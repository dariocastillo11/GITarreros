#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/timer.h>
#include <linux/gpio.h>
#include <linux/device.h>

#define DEVICE_NAME "mis_senales"

// Module parameters for GPIO pins
static int gpio_pin1 = 4;
static int gpio_pin2 = 17;
module_param(gpio_pin1, int, S_IRUGO);
module_param(gpio_pin2, int, S_IRUGO);

static int canal_activo = 0; // 0 = Señal 1, 1 = Señal 2
static int major_number;
static struct timer_list mi_timer;

static struct class*  my_class  = NULL;
static struct device* my_device = NULL;

static int gpio_requested1 = 0;
static int gpio_requested2 = 0;

// Simple global variables for sampled values
static unsigned long ultimo_tiempo = 0;
static int ultimo_valor1 = 0;
static int ultimo_valor2 = 0;

// ---- TIMER DEL KERNEL (Muestreo cada 1 segundo) ----
static void mi_timer_callback(struct timer_list *t) {
    unsigned long tiempo_actual = jiffies / HZ;
    ultimo_tiempo = tiempo_actual;

    // Muestreo Señal 1 (Senoidal)
    if (gpio_requested1) {
        ultimo_valor1 = gpio_get_value(gpio_pin1) ? 1000 : 0;
    } else {
        // Simulación de onda senoidal discreta en el rango 0..1000
        static const int sine_table[8] = { 500, 853, 1000, 853, 500, 146, 0, 146 };
        ultimo_valor1 = sine_table[tiempo_actual % 8];
    }

    // Muestreo Señal 2 (Cuadrada)
    if (gpio_requested2) {
        ultimo_valor2 = gpio_get_value(gpio_pin2) ? 1000 : 0;
    } else {
        // Simulación de onda cuadrada en el rango 0 o 1000
        ultimo_valor2 = (tiempo_actual % 2 == 0) ? 1000 : 0;
    }

    mod_timer(&mi_timer, jiffies + msecs_to_jiffies(1000));
}

// ---- OPERACIONES DEL ARCHIVO DE DISPOSITIVO ----

static int device_open(struct inode *inode, struct file *file) {
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    return 0;
}

static ssize_t device_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset) {
    char k_buf[2];
    
    if (len > 1) len = 1;
    
    if (copy_from_user(k_buf, buffer, len)) {
        return -EFAULT;
    }

    if (k_buf[0] == '1' || k_buf[0] == '0') {
        canal_activo = 0; // Señal 1
    } else if (k_buf[0] == '2') {
        canal_activo = 1; // Señal 2
    }

    return len;
}

static ssize_t device_read(struct file *file, char __user *buffer, size_t len, loff_t *offset) {
    char k_response[64];
    size_t response_len;
    int valor_actual;

    // Control estricto anti-bucle de lectura
    if (*offset > 0) {
        return 0;
    }

    if (canal_activo == 0) {
        valor_actual = ultimo_valor1;
    } else {
        valor_actual = ultimo_valor2;
    }

    // Formateo compatible con reader.c: "<canal> <tiempo> <valor>\n"
    memset(k_response, 0, sizeof(k_response));
    snprintf(k_response, sizeof(k_response) - 1, "%d %lu %d\n", canal_activo + 1, ultimo_tiempo, valor_actual);
    response_len = strlen(k_response);

    if (len < response_len) {
        return -EINVAL;
    }

    // Copia directa al espacio de usuario
    if (copy_to_user(buffer, k_response, response_len)) {
        return -EFAULT;
    }

    *offset += response_len;
    return response_len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
};

static int __init mi_driver_init(void) {
    // 1. Registrar dispositivo de caracteres
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        return major_number;
    }

    // 2. Crear clase de dispositivo en /sys/class
    my_class = class_create(THIS_MODULE, "mis_senales_class");
    if (IS_ERR(my_class)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(my_class);
    }

    // 3. Crear nodo de dispositivo en /dev/mis_senales
    my_device = device_create(my_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(my_device)) {
        class_destroy(my_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(my_device);
    }

    // 4. Configurar e inicializar GPIOs
    if (gpio_request(gpio_pin1, "signal1") == 0) {
        gpio_direction_input(gpio_pin1);
        gpio_requested1 = 1;
        pr_info("Driver: GPIO %d solicitado con éxito para Señal 1\n", gpio_pin1);
    } else {
        pr_warn("Driver: No se pudo solicitar GPIO %d, usando simulación para Señal 1\n", gpio_pin1);
    }

    if (gpio_request(gpio_pin2, "signal2") == 0) {
        gpio_direction_input(gpio_pin2);
        gpio_requested2 = 1;
        pr_info("Driver: GPIO %d solicitado con éxito para Señal 2\n", gpio_pin2);
    } else {
        pr_warn("Driver: No se pudo solicitar GPIO %d, usando simulación para Señal 2\n", gpio_pin2);
    }

    // 5. Configurar timer de muestreo
    timer_setup(&mi_timer, mi_timer_callback, 0);
    mod_timer(&mi_timer, jiffies + msecs_to_jiffies(1000));

    pr_info("Driver: Inicializado correctamente con major %d\n", major_number);
    return 0;
}

static void __exit mi_driver_exit(void) {
    del_timer(&mi_timer);
    
    if (gpio_requested1) {
        gpio_free(gpio_pin1);
    }
    if (gpio_requested2) {
        gpio_free(gpio_pin2);
    }

    device_destroy(my_class, MKDEV(major_number, 0));
    class_destroy(my_class);
    unregister_chrdev(major_number, DEVICE_NAME);

    pr_info("Driver: Descargado correctamente\n");
}

module_init(mi_driver_init);
module_exit(mi_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("GITarreros");
MODULE_DESCRIPTION("CDD con soporte GPIO y fallback de simulación");