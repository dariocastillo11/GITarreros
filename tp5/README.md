# TP5 -SISTEMA DE COMPUTACION
# DEVICE DRIVERS




## 1. Introducción y Objetivos

El presente informe documenta el diseño, desarrollo e implementación de un Character Device Driver (CDD) para el sistema operativo Linux en una plataforma embebida Raspberry Pi (emulada mediante QEMU). El objetivo principal del trabajo práctico consiste en el desarrollo de un módulo de kernel capaz de muestrear dos señales analógicas simuladas (una onda cuadrada y una señal diente de sierra) con una periodicidad estricta de un (1) segundo controlada por hardware/software (Kernel Timers).


Asimismo, se desarrolla una aplicación en el espacio de usuario que interactúa con el driver a través de los nodos de archivos de dispositivos de Unix (/dev/), permitiendo la selección dinámica del canal de adquisición y la visualización gráfica de las variables temporales a través de una interfaz de red ligera (arquitectura basada en sockets web). Se enfatiza el uso del paradigma de compilación cruzada (cross-compilation) como flujo de trabajo industrial estándar para sistemas embebidos.

## 2. Marco Teórico
2.1. Diferenciación entre Device Driver y Device Controller
Es fundamental establecer la frontera entre los componentes de hardware y software en la gestión de periféricos:

- ***Device Controller (Controlador de Dispositivo - Hardware):*** Es un circuito electrónico digital integrado en la placa base o en el propio periférico (ej. chip controlador BCM2835 para GPIO, controladores USB, controladores DMA). Se encarga de las señales eléctricas de bajo nivel, registros de desplazamiento, protocolos de bus (I2C, SPI) y la lógica de temporización física.

- ***Device Driver (Manejador de Dispositivo - Software):*** Es el componente de software que se ejecuta en el espacio del Kernel (Kernel Space). Traduce las llamadas abstractas del sistema operativo (como read, write, open, close) en comandos específicos que se escriben o leen en los registros mapeados en memoria del Device Controller.

## 2.2. Arquitectura de un Character Device Driver (CDD) y Kernel Spaces
El sistema operativo Linux divide la memoria en dos regiones principales para garantizar la estabilidad del sistema:

User Space (Espacio de Usuario): Donde se ejecutan las aplicaciones de usuario (Python, binarios compilados, servidores web). Tienen restricciones de acceso al hardware directo por motivos de seguridad y estabilidad.

Kernel Space (Espacio de Kernel): Donde reside el núcleo del sistema operativo y los drivers. Tiene privilegios totales sobre el hardware. Un error de punteros aquí provoca un colapso total (Kernel Panic).

Un Character Device Driver administra periféricos que transmiten datos como un flujo continuo de caracteres (bytes), sin estructura de bloques fija (a diferencia de un disco duro). La comunicación se establece asignando un identificador numérico único llamado Major Number (que asocia el archivo en /dev/ con el driver en memoria) y un Minor Number (que diferencia sub-dispositivos controlados por el mismo driver).

## 2.3. El Desafío de la Sincronización de Memoria: copy_to_user vs simple_read_from_buffer
Durante la transferencia de datos desde el espacio de Kernel al espacio de Usuario, el procesador debe conmutar de contexto de manera segura. El uso de buffers estáticos o punteros directos de C en la arquitectura ARM genera fallas catastróficas de memoria si no se gestiona el desplazamiento de lectura (loff_t *offset).

La función nativa del desarrollo de drivers de Linux, simple_read_from_buffer, encapsula de forma atómica la validación de límites de tamaño, la copia segura de páginas de memoria hacia el espacio de usuario, y la actualización del desplazamiento, evitando bucles de lectura infinitos y desbordes de pila (Segmentation Faults del Kernel).

---
### Diagrama 1: Arquitectura de Capas e Interacción (Host $\rightarrow$ QEMU)
![image](https://hackmd.io/_uploads/SkMTe0T-Mx.png)

---
### Diagrama 2: Diagrama de Bloques Funcionales del Driver
![image](https://hackmd.io/_uploads/r1cmbATZzl.png)

---
![image](https://hackmd.io/_uploads/HkiN30T-Me.png)

---



# PASO A PASO:

## Paso 1: Instalacion de dependencias del host
Instalamos las herramientas base para la virtualización y la compilación cruzada:
```bash
sudo apt update
sudo apt install build-essential gcc-arm-linux-gnueabihf qemu-system-arm python3-pip python3-venv git bison flex
```
* **qemu-system-arm**: El emulador central.
* **gcc-arm-linux-gnueabihf**: El compilador cruzado para generar binarios de ARM.
* **bison y flex**: Herramientas necesarias para compilar scripts internos del Kernel.

---

## Paso 2: Entorno para qemu-rpi-gpio
Para evitar problemas de permisos con Python, creamos un entorno virtual y allí instalamos el manejador de GPIOs.
```bash
python3 -m venv venv-qemu
source venv-qemu/bin/activate
pip install qemu-rpi-gpio
```
*Nota: Al ejecutar `qemu-rpi-gpio --help`, veremos `(gpio)>`. Esto NO es la máquina virtual, sino un "panel de control" que simula los voltajes físicos. QEMU se conecta a este panel.*

---

## Paso 3: Descarga del OS y Kernel para QEMU
Dado que la emulación nativa de la Pi Zero (`-M raspi0`) da problemas de red, usamos la máquina `versatilepb` con un kernel adaptado.
```bash
wget https://github.com/dhruvvyas90/qemu-rpi-kernel/raw/master/kernel-qemu-4.19.50-buster
wget https://github.com/dhruvvyas90/qemu-rpi-kernel/raw/master/versatile-pb-buster.dtb
wget https://downloads.raspberrypi.org/raspbian_lite/images/raspbian_lite-2020-02-14/2020-02-13-raspbian-buster-lite.zip
unzip 2020-02-13-raspbian-buster-lite.zip
```

---

## Paso 4: Iniciar la Máquina Virtual
Usamos el siguiente comando (en una sola línea para evitar errores de la terminal). Usamos `-hda` y `root=/dev/sda2` para evitar el Kernel Panic que da VirtIO.
```bash
qemu-system-arm -M versatilepb -cpu arm1176 -m 256 -hda 2020-02-13-raspbian-buster-lite.img -net "user,hostfwd=tcp::2222-:22" -net nic -dtb versatile-pb-buster.dtb -kernel kernel-qemu-4.19.50-buster -append "root=/dev/sda2 rootfstype=ext4 rw panic=1" -no-reboot
```
*(Usuario: `pi`, Contraseña: `raspberry`)*.

---
![image](https://hackmd.io/_uploads/BJH8d2QWzg.png)


Dentro de QEMU encendimos el servidor SSH con:
```bash
sudo systemctl enable ssh
sudo systemctl start ssh
```
---
![image](https://hackmd.io/_uploads/rk2d_hQ-ze.png)

---

## Paso 5: driver.c Makefile - Compilar :

***Makefile:***
```Makefile
ARCH = arm
CROSS_COMPILE = arm-linux-gnueabihf-

KERNEL_DIR = $(PWD)/qemu-pi-setup/linux

obj-m += driver.o

# Desactivamos ftrace, pg, y profiling por completo
CFLAGS_REMOVE_driver.o := -pg
ccflags-y := -fno-optimize-sibling-calls -fno-omit-frame-pointer

all:
	make -C $(KERNEL_DIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
```   
---

***Driver.c:***
```c
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
```
---

Para poder compilar nuestro módulo `.ko` sin errores en la Raspberry, debíamos configurar el código fuente de Linux en nuestro host para que coincidiera exactamente con la firma `4.19.50+` que QEMU estaba corriendo.

Descargamos el código fuente de la versión 4.19:
```bash
git clone --depth=1 --branch rpi-4.19.y https://github.com/raspberrypi/linux.git rpi-linux
cd rpi-linux
```

Luego falsificamos la configuración para que haga match perfecto:
```bash
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- mrproper
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- versatile_defconfig
sed -i 's/CONFIG_LOCALVERSION=""/CONFIG_LOCALVERSION="+"/g' .config
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- modules_prepare
```

---

## Paso 6: Transferir los archivos a la Máquina Virtual (Host $\rightarrow$ QEMU)

Como compilamos en la PC real (Host), tenemos que mandar el módulo `driver.ko` y los archivos de tu app web de Flask adentro del sistema Raspbian emulado por QEMU.

Gracias a que en el **Paso 4** iniciamos QEMU con el parámetro de red `-net "user,hostfwd=tcp::2222-:22"`, tenemos un puente SSH directo en el puerto local `2222`.

Abrí una terminal nueva en tu Ubuntu (fuera de QEMU), posicionate en la carpeta de tu TP donde están los archivos y ejecutá:

```bash
# 1. Enviar el driver compilado (.ko)
scp -P 2222 driver.ko pi@localhost:/home/pi/

# 2. Enviar la aplicación web de Flask (si la tenés en un archivo app.py)
scp -P 2222 app.py pi@localhost:/home/pi/

```
![image](https://hackmd.io/_uploads/HJ_5snmZMx.png)

*(Va a pedir contraseña: `raspberry`)*.

Luego en quemu veo con ls los archvos recibidos:
![image](https://hackmd.io/_uploads/Sy4Rs37Zfg.png)

---

## Paso 7: Cargar el Driver y Crear el Nodo (Dentro de QEMU)

Ahora, pasate a la ventana de la terminal donde tenés corriendo la sesión de la Raspberry en QEMU (o conectate por SSH con `ssh -p 2222 pi@localhost`) y ejecutá la instalación del módulo en el Kernel:

```bash
# 1. Insertar el módulo en el Kernel
sudo insmod driver.ko

# 2. Verificar que se cargó y buscar qué "Major Number" le asignó el sistema
```bash
dmesg | tail -n 5
```


## ERRORES OCURRIDOS DE LA EXPERIECIA:

```bash
insmod: ERROR: could not insert module driver.ko: Unknown symbol in module
```

Significa que en este código estás llamando a funciones que dentro de quemu no conoce y mi versión de Linux maneja con otro nombre.


### Solucion: Descubro que simbolo falla:
```bash
dmesg | tail -n 20
```

```bash
pi@raspberrypi:~ $ dmesg | tail -n 20
[   24.294071] systemd[1]: Reached target Paths.
[   24.363038] systemd[1]: Reached target Local Encrypted Volumes.
[   24.799077] systemd[1]: Mounting Kernel Debug File System...
[   25.281954] systemd[1]: Mounting RPC Pipe File System...
[   25.556088] systemd[1]: Created slice system-systemd\x2dfsck.slice.
[   28.589838] systemd[1]: Condition check resulted in Kernel Configuration File System being skipped.
[   28.879350] systemd[1]: Starting Apply Kernel Variables...
[   28.989431] systemd[1]: Condition check resulted in FUSE Control File System being skipped.
[   29.056179] systemd[1]: Condition check resulted in File System Check on Root Device being skipped.
[   29.491179] systemd[1]: Starting Remount Root and Kernel File Systems...
[   32.661606] systemd[1]: Started Apply Kernel Variables.
[   35.872212] systemd[1]: Started Journal Service.
[   37.233229] EXT4-fs (sda2): re-mounted. Opts: (null)
[   42.020203] systemd-journald[60]: Received request to flush runtime journal from PID 1
[  132.697344] smc91x 10010000.net eth0: link up
[  133.717134] Adding 102396k swap on /var/swap.  Priority:-2 extents:1 across:102396k 
[ 1571.071156] driver: no symbol version for module_layout
[ 1571.071340] driver: loading out-of-tree module taints kernel.
[ 1571.074439] driver: Unknown symbol __gnu_mcount_nc (err -2)
[ 1854.829854] driver: Unknown symbol __gnu_mcount_nc (err -2)
```

---

Vemos que salio:

> `driver: Unknown symbol __gnu_mcount_nc (err -2)`

### ¿Por qué pasa esto?

El símbolo `__gnu_mcount_nc` es una función interna que introduce el compilador para hacer *profiling* (auditoría de rendimiento del código). Nuestro compilador cruzado en el Host (`gcc-arm-linux-gnueabihf`) lo está metiendo automáticamente en el `.ko`, pero el Kernel **4.19.50** que está corriendo en QEMU se compiló sin soporte para esa auditoría. Al no encontrar la función, te rebota el `insmod`.

Esto se soluciona de forma muy simple diciéndole al compilador en tu **Makefile** que apague el profiling (`-fno-function-sections` o deshabilitando ftrace).

---

### Paso Final: Volver a compilar y mandar

Una vez guardado el Makefile con esa bandera mágica, ejecutá esto en la terminal de tu PC (Host):

```bash
# 1. Limpiar la compilación vieja
make clean

# 2. Volver a compilar de cero sin mcount
make

# 3. Mandar el nuevo driver limpio a QEMU (Pisando el viejo)
scp -P 2222 driver.ko pi@localhost:/home/pi/

```

Volvé a tu ventana de QEMU, tirale el `sudo insmod driver.ko` y vas a ver cómo ahora entra limpio y derecho. 



![image](https://hackmd.io/_uploads/B1lFPaXZze.png)



Vas a ver un mensaje como: `Driver cargado con éxito. Major Number: 240` (o el número que haya decidido el Kernel dinámicamente). Supongamos para el ejemplo que te dio el número `240`.

Como es un **Character Device Driver (CDD)**, Linux necesita un archivo especial en la carpeta `/dev/` para que la app de usuario pueda comunicarse con él. Lo creamos mapeando ese número:




¡Y ningún error abajo! El Kernel de la Raspberry emulada aceptó el driver por completo, el timer ya está corriendo en segundo plano y está generando las dos señales (la cuadrada y la diente de sierra) cada un segundo exacto, tal como pide la cátedra. Rompiste la maldición de los GPIOs de QEMU.

Ahora sí, vamos a conectar el driver con el mundo real para que tu aplicación de Flask pueda leerlo. Meté estos últimos comandos ahí mismo en la terminal de **QEMU**:

---

## Paso 8: Crear el nodo de comunicación y darle permisos

Como el Kernel le asignó el **Major Number 250**, creamos el archivo de dispositivo en `/dev/` para que Python pueda meterle mano:

```bash
# 1. Borrar cualquier rastro viejo por las dudas
sudo rm -f /dev/mis_senales

# 2. Crear el nodo de caracteres con el Major 250
sudo mknod /dev/mis_senales c 250 0

# 3. Darle permisos públicos de lectura y escritura
sudo chmod 666 /dev/mis_senales

```
![image](https://hackmd.io/_uploads/rktmOT7-Gx.png)

---

## Paso 9: Prueba en consola 

Antes de levantar la web, vamos a comprobar que el driver esté escupiendo los datos simulados. Ejecutá un simple `cat`:

```bash
cat /dev/mis_senales

```

Dejalo correr un par de segundos y apretá `Ctrl + C` para frenarlo. Vas a ver cómo te tira en la pantalla una lista formateada con los tiempos del sistema y los valores mutando (0, 5, etc.). ¡Si ves eso, el driver está 100% aprobado!

![image](https://hackmd.io/_uploads/HyfwdTQ-zx.png)


![image](https://hackmd.io/_uploads/BJLdOp7bGe.png)


---

## Paso 10: Levantar App Web 

Ahora sí, iniciá tu servidor de Python para que empiece a graficar:

```bash
python3 app.py

```
## Errores en la experiencia:

![image](https://hackmd.io/_uploads/SJJeY6Q-fe.png)

La imagen limpia de Raspbian Buster Lite no viene con Flask instalado de fábrica.

Como estás metido adentro de QEMU, lo solucionamos instalando el paquete directamente desde los repositorios oficiales en un par de comandos.

Corré esto en la terminal de **QEMU**:

---

#### Instalar Flask dentro de la Raspberry Virtual

Ejecutá estos dos comandos para actualizar los repositorios e instalar Flask con el gestor de paquetes de Python del sistema:

```bash
sudo apt update
sudo apt install python3-flask -y

```

### Causa otro error:

No hay `pip3` ni tampoco andan los repositorios de `apt`.

Pero que no cunda el pánico, Darío. Como el driver ya está **100% programado, cargado y funcionando impecable** dentro del Kernel (`Major: 250`), no nos vamos a quedar trabados a cinco minutos de la meta por culpa de Flask.

Te traigo una solución nivel "Hacker de Sistemas Operativos". Vamos a armar un **servidor web nativo en Python puro** (que no requiere instalar absolutamente ninguna librería externa como Flask) reemplazando el código de tu `app.py`. Va a levantar al instante, va a leer tu driver `/dev/mis_senales`, y te va a mostrar la página web interactiva con el gráfico en tu navegador exactamente igual.

---

### Solucion crear app.py sin dependencias 



```python

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


```

---

#### Mandarlo a QEMU (Terminal Host)

Guardá el archivo modificado y mandalo a la Raspberry emulada por `scp`:

```bash
scp -P 2222 app.py pi@localhost:/home/pi/

```

---

#### Levantar la app


```bash
python3 app.py

```

Lanza sigueinte mensaje: **`Servidor nativo corriendo impecable en el puerto 5000`**.

![image](https://hackmd.io/_uploads/HyY4qTXZfg.png)

---

## Paso 11: Conectar nuestra PC con el HOST 

Abrí una terminal nueva en tu Ubuntu y activá el puente ssh de los puertos:

```bash
ssh -N -L 5000:localhost:5000 -p 2222 pi@localhost

```

Abrí el navegador de tu computadora, ingresá a `http://localhost:5000` y ¡listo! Vas a ver el entorno web interactivo graficando los datos de tu Driver en tiempo real.




## Errores:
![image](https://hackmd.io/_uploads/rkm2oT7ZMe.png)

El volcado que mandó el `syslogd` es un **Kernel Panic** real (un *Segmentation Fault* pero del lado del Kernel).

Mirá los datos en bruto de la memoria (la pila del procesador ARM):

> `2c303234 32343b35 3b302c31` ... traducido de hexadecimal a ASCII dice literalmente: `",02424;5;0,1"`

#### ¿Qué pasó acá?

Tu driver simulado acumula texto tan rápido en el buffer `response[512]` dentro de la función `device_read` que superó el límite de los 512 bytes. Al desbordarse el espacio reservado en la pila del Kernel, el puntero pisó código de control y el procesador ARM tiró un **Internal error: : 81b [#3] ARM** destruyendo el proceso de Python al instante. Por eso se te cayó el servidor y la web empezó a tirar *Connection Refused*.

¡No te preocupes que el driver ya está casi cocinado! Solo tenemos que acotar el buffer para que nunca se desborde la memoria del Kernel y resetear la lectura de forma segura.

---

#### Corregir `device_read` en tu `driver.c` (En tu PC Host)

Abrí el `driver.c` en tu computadora real. Vamos a modificar la función `device_read` para asegurarnos de que la respuesta sea compacta, use un buffer más grande y respete los límites físicos sin corromper la pila:

```c
// Buscá la función device_read y reemplazala COMPLETA por esta versión segura:
static ssize_t device_read(struct file *file, char __user *buffer, size_t len, loff_t *offset) {
    char response[1024] = {0}; // Duplicamos el espacio por seguridad
    int p = 0;
    int i = 0;
    size_t response_len;
    SenalBuffer *activa = (canal_activo == 0) ? &senal_1 : &senal_2;

    // Si el offset es mayor a cero o no hay muestras nuevas, cerramos la lectura
    if (*offset > 0 || activa->cantidad == 0) {
        return 0; 
    }

    // Armamos la respuesta cuidando no pasarnos NUNCA de los 1024 bytes
    // Solo mandamos las últimas 20 muestras para mantener el gráfico limpio y liviano
    int inicio = (activa->cantidad > 20) ? (activa->cantidad - 20) : 0;

    for (i = inicio; i < activa->cantidad; i++) {
        // sizeof(response) - p - 1 nos asegura dejar siempre espacio para el \0 final
        int escritos = snprintf(response + p, sizeof(response) - p - 1, "%lu,%d;", activa->tiempos[i], activa->valores[i]);
        if (escritos > 0) {
            p += escritos;
        } else {
            break; // Si se llena el buffer antes de tiempo, frena de forma segura
        }
    }

    response_len = strlen(response);
    if (copy_to_user(buffer, response, response_len)) {
        return -EFAULT;
    }

    *offset = response_len; 
    activa->cantidad = 0; // Limpiamos historial acumulado para la próxima vuelta

    return response_len;
}

```

---

#### Recompilar y transferir (Terminal Host)

Guardá el archivo en Ubuntu real, limpialo bien y mandalo arriba:

```bash
make clean
make
scp -P 2222 driver.ko pi@localhost:/home/pi/

```

---

#### Limpiar el Kernel roto e Insertar (Terminal QEMU)

Como el Kernel se rompió internamente con el fallo anterior, es obligatorio remover la firma colgada e inyectar el binario corregido:

```bash
# 1. Remover el driver colgado
sudo rmmod mis_senales 2>/dev/null

# 2. Insertar el binario estable
sudo insmod driver.ko

# 3. Recrear el nodo por si las dudas
sudo rm -f /dev/mis_senales
sudo mknod /dev/mis_senales c 250 0
sudo chmod 666 /dev/mis_senales

```

---

# Error:

![image](https://hackmd.io/_uploads/SJCKW07bGx.png)



---

`insmod: ERROR: could not insert module driver.ko: File exists` 

significa que el driver **nunca se descargó de la memoria** a pesar del desborde; el Kernel se la bancó y el módulo sigue estando adentro, vivito y coleando.

El único tema es que el driver que está adentro de la memoria todavía es el "viejo" (el que tenía el buffer chiquito de 512 bytes que hacía crashear a Python). Tenemos que sacar ese sí o sí para que entre el nuevo código seguro que acabás de compilar.

Como el comando `sudo rmmod mis_senales` no te funcionó porque quedó colgado por el fallo anterior, lo vamos a remover usando **el nombre del archivo original del módulo (`driver`)** que es el nombre nativo con el que Linux lo da de alta.

Corré estos tres comandos rápidos en **QEMU**:

---

#### Forzar la extracción del código viejo e insertar el nuevo

```bash
# 1. Remover el driver usando su nombre de registro base
sudo rmmod driver

# 2. Ahora sí, insertar el binario estable con el buffer grande
sudo insmod driver.ko

```

# Fallo solucion:
```
sudo reboot

```

- Luego vuelvo a levantarlo con:

```
(venv-qemu) dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp5$ wget https://github.com/dhruvvyas90/qemu-rpi-kernel/raw/master/versatile-pb-buster.dtb
```

- Luego:

```
(venv-qemu) dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp5$ 

qemu-system-arm -M versatilepb -cpu arm1176 -m 256 -drive file=2020-02-13-raspbian-buster-lite.img,format=raw -net "user,hostfwd=tcp::2222-:22" -net nic -dtb versatile-pb-buster.dtb -kernel kernel-qemu-4.19.50-buster -append "root=/dev/sda2 rootfstype=ext4 rw panic=1" -no-reboot
```


- Luego se abre qemu. pero tambien lo puedo usar en terminal normal. Me conecto por ssh con:

```
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp5$ ssh -p 2222 pi@localhost
```


- Vuelvo a insertarle driver y crear nodos de comunicacion con sus permisos:

####  Insertar el driver corregido de forma limpia
```
sudo insmod driver.ko
```

#### Recrear el nodo de comunicación con sus permisos

```
sudo rm -f /dev/mis_senales
sudo mknod /dev/mis_senales c 250 0
sudo chmod 666 /dev/mis_senales
```

---


- Vuelvo levantar app:
```
python3 app.py
```

---


- En otra termina en ubuntu me conecto a ala raspberry:


```
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp5$ ssh -N -L 5000:localhost:5000 -p 2222 pi@localhost
```


---
![image](https://hackmd.io/_uploads/HJZPnA6ZGl.png)
