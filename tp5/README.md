# TP5 — Driver de Kernel y Visualización Web sobre QEMU/Raspberry Pi

## Contexto

El objetivo del trabajo es escribir un **Character Device Driver (CDD)** para Linux que muestree dos señales simuladas y las exponga a través de un archivo de dispositivo (`/dev/mis_senales`). Una aplicación de usuario lee ese dispositivo y sirve los datos por HTTP para visualizarlos desde el navegador del host.

Todo el desarrollo y la compilación ocurren en la **PC anfitriona (host)**. Los binarios resultantes se transfieren a la Raspberry Pi (o a QEMU que la emula) por SSH. El flujo es idéntico ya sea que se use hardware real o el emulador.

---

## Herramientas necesarias en el Host

```bash
sudo apt update
sudo apt install build-essential gcc-arm-linux-gnueabihf \
    qemu-system-arm python3-pip python3-venv git bison flex
```

| Paquete | Para qué sirve |
|---|---|
| `gcc-arm-linux-gnueabihf` | Compilador cruzado para ARM (genera binarios para la Pi desde una PC x86) |
| `qemu-system-arm` | Emulador de la arquitectura ARM |
| `bison` / `flex` | Requeridos al preparar los headers del kernel |

---

## Entorno virtual para qemu-rpi-gpio (opcional)

Si se quiere simular los pines GPIO físicos desde el host:

```bash
python3 -m venv venv-qemu
source venv-qemu/bin/activate
pip install qemu-rpi-gpio
```

El prompt `(gpio)>` que aparece al ejecutar `qemu-rpi-gpio` **no es la máquina virtual**; es el panel de control que simula los voltajes. QEMU se conecta a él por socket.

---

## Imagen y kernel para QEMU

Se usa la máquina `versatilepb` con un kernel adaptado porque la emulación nativa de la Pi Zero (`-M raspi0`) presenta problemas de red.

```bash
wget https://github.com/dhruvvyas90/qemu-rpi-kernel/raw/master/kernel-qemu-4.19.50-buster
wget https://github.com/dhruvvyas90/qemu-rpi-kernel/raw/master/versatile-pb-buster.dtb
wget https://downloads.raspberrypi.org/raspbian_lite/images/raspbian_lite-2020-02-14/2020-02-13-raspbian-buster-lite.zip
unzip 2020-02-13-raspbian-buster-lite.zip
```

---

## Arranque de QEMU

```bash
qemu-system-arm \
  -M versatilepb \
  -cpu arm1176 \
  -m 256 \
  -drive file=2020-02-13-raspbian-buster-lite.img,format=raw \
  -net "user,hostfwd=tcp::2222-:22" \
  -net nic \
  -dtb versatile-pb-buster.dtb \
  -kernel kernel-qemu-4.19.50-buster \
  -append "root=/dev/sda2 rootfstype=ext4 rw panic=1" \
  -no-reboot
```

Credenciales por defecto: usuario `pi`, contraseña `raspberry`.

Para habilitar SSH dentro de QEMU (solo la primera vez):

```bash
sudo systemctl enable ssh
sudo systemctl start ssh
```

Desde ese momento se puede trabajar cómodamente desde el host:

```bash
ssh -p 2222 pi@localhost
```

---

## Headers del kernel para compilación cruzada

El módulo `.ko` debe compilarse contra los **headers exactos** del kernel que corre en QEMU (versión `4.19.50+`), o el `insmod` falla con `version magic mismatch`.

```bash
git clone --depth=1 --branch rpi-4.19.y https://github.com/raspberrypi/linux.git rpi-linux
cd rpi-linux

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- mrproper
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- versatile_defconfig

# Ajustar el LOCALVERSION para que coincida exactamente con el kernel de QEMU
sed -i 's/CONFIG_LOCALVERSION=""/CONFIG_LOCALVERSION="+"/g' .config

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- modules_prepare
```

---

## El driver — `driver.c`

El driver registra un Character Device, arranca un kernel timer que muestrea cada segundo y expone los datos a través de las operaciones estándar `read`/`write` del archivo de dispositivo.

Como QEMU no tiene GPIOs físicos, las señales se generan de forma sintética:

- **Señal 1:** onda cuadrada que alterna entre 0 y 5.
- **Señal 2:** diente de sierra que recorre de 0 a 9 y se reinicia.

```c
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

static unsigned long ultimo_tiempo = 0;
static int ultimo_valor = 0;

static void mi_timer_callback(struct timer_list *t) {
    unsigned long tiempo_actual = jiffies / HZ;
    ultimo_tiempo = tiempo_actual;

    if (canal_activo == 0) {
        ultimo_valor = (tiempo_actual % 2 == 0) ? 5 : 0;  // Cuadrada
    } else {
        ultimo_valor = (int)(tiempo_actual % 10);           // Diente de sierra
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
```

---

## El Makefile

La bandera `ccflags-y` desactiva el profiling que introduce el compilador cruzado y que el kernel de QEMU no tiene exportado (`__gnu_mcount_nc`). Sin ella el `insmod` falla con `Unknown symbol`.

```makefile
ARCH         = arm
CROSS_COMPILE = arm-linux-gnueabihf-
KERNEL_DIR   = $(PWD)/rpi-linux

obj-m += driver.o

ccflags-y := -fno-pic -mno-single-pic-base -fno-common \
             -fno-delete-null-pointer-checks -O2

all:
	make -C $(KERNEL_DIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
```

> Los espacios antes de `make` en las reglas deben ser **tabulaciones**, no espacios.

---

## Compilación cruzada

```bash
make clean
make
```

Si todo sale bien se genera `driver.ko` en la misma carpeta.

---

## La aplicación web — `server.py`

La aplicación corre dentro de QEMU, lee `/dev/mis_senales` y sirve los datos por HTTP. No requiere Flask ni ninguna librería externa.

```python
import http.server
import socketserver
import os

PORT = 5000
DEVICE = "/dev/mis_senales"

HTML = """<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>Monitor de Señales</title>
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  <style>
    body { font-family: Arial, sans-serif; background: #f4f4f9;
           display: flex; flex-direction: column; align-items: center; padding: 30px; }
    h2   { color: #333; }
    button { padding: 10px 24px; margin: 6px; font-size: 15px; cursor: pointer;
             border: none; border-radius: 6px; background: #007bff; color: #fff; }
    button.active { background: #28a745; }
    canvas { max-width: 800px; width: 100%; margin-top: 20px; }
  </style>
</head>
<body>
  <h2>Monitor de Señales — Kernel Driver</h2>
  <div>
    <button id="b0" class="active" onclick="cambiar(0)">Señal 1 — Cuadrada</button>
    <button id="b1"               onclick="cambiar(1)">Señal 2 — Diente de sierra</button>
  </div>
  <canvas id="chart"></canvas>

  <script>
    const ctx   = document.getElementById('chart').getContext('2d');
    const chart = new Chart(ctx, {
      type: 'line',
      data: {
        labels: [],
        datasets: [{
          label: 'Valor',
          data: [],
          borderColor: '#007bff',
          backgroundColor: 'rgba(0,123,255,0.08)',
          tension: 0.3,
          fill: true,
          pointRadius: 4
        }]
      },
      options: {
        animation: false,
        scales: {
          x: { title: { display: true, text: 'Tiempo (s)' } },
          y: { min: -1, max: 11, title: { display: true, text: 'Valor' } }
        }
      }
    });

    // Mantiene un historial de los últimos 30 puntos
    const MAX = 30;
    const tiempos = [];
    const valores = [];

    function cambiar(canal) {
      fetch('/cambiar?canal=' + canal);
      document.getElementById('b0').className = canal === 0 ? 'active' : '';
      document.getElementById('b1').className = canal === 1 ? 'active' : '';
      chart.data.datasets[0].borderColor = canal === 0 ? '#007bff' : '#28a745';
    }

    async function actualizar() {
      try {
        const res  = await fetch('/data');
        const text = await res.text();
        text.split(';').filter(p => p.includes(',')).forEach(p => {
          const [t, v] = p.split(',');
          tiempos.push(t);
          valores.push(parseInt(v));
          if (tiempos.length > MAX) { tiempos.shift(); valores.shift(); }
        });
        chart.data.labels          = tiempos;
        chart.data.datasets[0].data = valores;
        chart.update();
      } catch (e) { console.error(e); }
    }

    setInterval(actualizar, 1000);
  </script>
</body>
</html>"""

class Handler(http.server.SimpleHTTPRequestHandler):
    def log_message(self, *args): pass   # silencia el log por defecto

    def do_GET(self):
        if self.path == '/':
            self._reply(200, 'text/html; charset=utf-8', HTML.encode())

        elif self.path == '/data':
            try:
                with open(DEVICE, 'r') as f:
                    data = f.read()
            except Exception:
                data = "0,0;"
            self._reply(200, 'text/plain', data.encode())

        elif self.path.startswith('/cambiar'):
            try:
                canal = self.path.split('=')[1]
                with open(DEVICE, 'w') as f:
                    f.write(canal)
            except Exception:
                pass
            self._reply(200, 'text/plain', b'ok')

        else:
            self.send_response(404)
            self.end_headers()

    def _reply(self, code, ctype, body):
        self.send_response(code)
        self.send_header('Content-Type', ctype)
        self.send_header('Content-Length', str(len(body)))
        self.end_headers()
        self.wfile.write(body)

with socketserver.TCPServer(('', PORT), Handler) as httpd:
    print(f'Servidor corriendo en el puerto {PORT}')
    httpd.serve_forever()
```

---

## Transferencia de binarios al emulador

```bash
# Desde la carpeta del proyecto en el host
scp -P 2222 driver.ko  pi@localhost:/home/pi/
scp -P 2222 server.py  pi@localhost:/home/pi/
```

---

## Carga del driver y creación del nodo (dentro de QEMU)

```bash
# Insertar el módulo
sudo insmod driver.ko

# Verificar que se cargó y obtener el major number
cat /proc/devices | grep mis_senales

# Crear el nodo de dispositivo (reemplazar 250 con el número real)
sudo rm -f /dev/mis_senales
sudo mknod /dev/mis_senales c 250 0
sudo chmod 666 /dev/mis_senales
```

Verificación rápida antes de levantar el servidor:

```bash
sleep 3 && cat /dev/mis_senales
# Salida esperada: 1542,5;  (tiempo del sistema, valor de la señal)
```

---

## Arranque del servidor web (dentro de QEMU)

```bash
python3 server.py
```

---

## Túnel SSH y visualización (en el host)

En una terminal nueva del host:

```bash
ssh -N -L 5000:localhost:5000 -p 2222 pi@localhost
```

Luego abrir en el navegador:

```
http://localhost:5000
```

El gráfico se actualiza cada segundo. Los botones permiten alternar entre la señal cuadrada y el diente de sierra.

---

## Advertencias normales al cargar el módulo

Al ejecutar `sudo insmod driver.ko` pueden aparecer estos mensajes en `dmesg`:

```
driver: no symbol version for module_layout
driver: loading out-of-tree module taints kernel.
```

Ambos son **advertencias esperadas** con este kernel de terceros y no afectan el funcionamiento. El módulo opera correctamente si `cat /proc/devices | grep mis_senales` devuelve una línea con el major number.

---

## Resumen del flujo completo

```
Host                             QEMU (Raspbian)
─────────────────────────────    ─────────────────────────────
Escribir driver.c + server.py
        │
make (cross-compile)
        │
scp driver.ko ──────────────────► sudo insmod driver.ko
scp server.py ──────────────────► sudo mknod /dev/mis_senales c <N> 0
                                  sudo chmod 666 /dev/mis_senales
                                  python3 server.py
        │
ssh -N -L 5000:localhost:5000
        │
Navegador → http://localhost:5000 ◄── datos del driver en tiempo real
```