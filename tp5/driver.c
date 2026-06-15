#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/timer.h>

#define DEVICE_NAME "mis_senales"

static int canal_activo = 0;
static int major_number;
static struct timer_list mi_timer;
static int contador_cuadrada = 0;

static unsigned long ultimo_tiempo = 0;
static int ultimo_valor = 0;

static void mi_timer_callback(struct timer_list *t) {
    unsigned long tiempo_actual = jiffies / HZ;
    ultimo_tiempo = tiempo_actual;

    if (canal_activo == 0) {
        ultimo_valor = (contador_cuadrada % 2 == 0) ? 5 : 0;
        contador_cuadrada++;
    } else {
        ultimo_valor = (int)(tiempo_actual % 10);
    }

    mod_timer(&mi_timer, jiffies + msecs_to_jiffies(1000));
}

static int device_open(struct inode *inode, struct file *file) { return 0; }
static int device_release(struct inode *inode, struct file *file) { return 0; }

static ssize_t device_write(struct file *file, const char __user *buffer,
                             size_t len, loff_t *offset) {
    char k_buf[2];
    if (len > 1) len = 1;
    if (copy_from_user(k_buf, buffer, len)) return -EFAULT;
    if (k_buf[0] == '0') canal_activo = 0;
    else if (k_buf[0] == '1') canal_activo = 1;
    return len;
}

static ssize_t device_read(struct file *file, char __user *buffer,
                            size_t len, loff_t *offset) {
    char k_response[32];
    size_t response_len;

    if (*offset > 0) return 0;

    memset(k_response, 0, sizeof(k_response));
    snprintf(k_response, sizeof(k_response) - 1, "%lu,%d;",
             ultimo_tiempo, ultimo_valor);
    response_len = strlen(k_response);

    if (len < response_len) return -EINVAL;
    if (copy_to_user(buffer, k_response, response_len)) return -EFAULT;

    *offset += response_len;
    return response_len;
}

static struct file_operations fops = {
    .owner   = THIS_MODULE,
    .open    = device_open,
    .release = device_release,
    .read    = device_read,
    .write   = device_write,
};

static int __init mi_driver_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) return major_number;

    timer_setup(&mi_timer, mi_timer_callback, 0);
    mod_timer(&mi_timer, jiffies + msecs_to_jiffies(1000));
    return 0;
}

static void __exit mi_driver_exit(void) {
    del_timer(&mi_timer);
    unregister_chrdev(major_number, DEVICE_NAME);
}

module_init(mi_driver_init);
module_exit(mi_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Equipo");
MODULE_DESCRIPTION("CDD con señales simuladas para QEMU");