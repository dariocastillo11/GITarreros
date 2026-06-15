
# Módulos del kernel

Breve descripción

Este informe documenta la compilación, firma e inserción de un módulo del kernel (`mimodulo`) y las comprobaciones realizadas en el sistema.

## Tabla de contenido

- [Requisitos](#requisitos)
- [Origen del módulo](#origen-del-módulo)
- [Compilación](#compilación)
- [Inserción y problema con Secure Boot](#inserción-y-problema-con-secure-boot)
- [Firma del módulo (MOK)](#firma-del-módulo-mok)
- [Verificación de carga](#verificación-de-carga)
- [Información del módulo](#información-del-módulo)
- [Listado de módulos y módulos no instalados](#listado-de-módulos-y-módulos-no-instalados)
- [Consideraciones de seguridad y diferencias con espacio de usuario](#consideraciones-de-seguridad-y-diferencias-con-espacio-de-usuario)
- [Herramientas útiles](#herramientas-útiles)

## Requisitos

Para trabajar con módulos del kernel es necesario tener instalados los headers de Linux. Se puede usar el siguiente comando:

```bash
sudo apt-get install build-essential checkinstall linux-source linux-headers-$(uname -r)
```

El uso de `$(uname -r)` asegura que se instalen los headers correspondientes al kernel activo en el sistema.


## Origen del módulo

El módulo desarrollado para este trabajo proviene de los archivos del repositorio:

[sistemas-de-computacion-unc/kenel-modules](https://gitlab.com/sistemas-de-computacion-unc/kenel-modules.git)

Se realizó un fork en:

[facumartinez431/kernel-modules](https://gitlab.com/facumartinez431/kernel-modules)



## Compilación

El repositorio contiene un `Makefile` que, al ejecutarse, realiza las siguientes acciones principales:

- `obj-m += mimodulo.o` declara `mimodulo.o` como objeto a compilar como módulo del kernel.
- `all`:
    - Ejecuta el sistema de compilación del kernel en `/lib/modules/$(shell uname -r)/build`. En este paso se usan los headers instalados y la configuración del kernel del sistema.
    - Compila el módulo en el directorio actual a partir de `mimodulo.c`.
- `clean`:
    - Ejecuta `make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean` para eliminar los artefactos generados por la compilación local.

Para limpiar el directorio de trabajo:

```bash
make clean
```



## Inserción y problema con Secure Boot

Al intentar insertar el módulo con:

```bash
sudo insmod mimodulo.ko
```

es posible obtener el siguiente error si el sistema tiene Secure Boot activado:

```
insmod: ERROR: could not insert module mimodulo.ko: Key was rejected by service
```

Se puede comprobar el estado de Secure Boot con:

```bash
sudo mokutil --sb-state
```

por ejemplo: `SecureBoot enabled`.

Al revisar el buffer del kernel con `dmesg` puede aparecer:

```
[ 4035.412720] Loading of unsigned module is rejected
```



## Firma del módulo (MOK)

Para permitir la carga de módulos no firmados se puede firmar el módulo y agregar la clave pública al MOK (Machine Owner Key). El flujo utilizado en este trabajo (Ubuntu) fue:

1. Generar un par de claves MOK (privada y pública) con OpenSSL:

```bash
openssl req -new -x509 -newkey rsa:2048 -keyout MOK.priv \
    -outform DER -out MOK.der -nodes -days 3650 \
    -subj "/CN=Module Sign key/"
```

La clave privada `MOK.priv` se utiliza para firmar el módulo; la clave pública `MOK.der` se añade al almacén de claves confiables.

2. Firmar el módulo:

```bash
sudo /lib/modules/$(uname -r)/build/scripts/sign-file sha256 MOK.priv MOK.der mimodulo.ko
```

3. Importar la clave pública al MOK:

```bash
sudo mokutil --import MOK.der
```

Tras importar la clave es necesario reiniciar el sistema para completar la carga de la clave pública en `.builtin_trusted_keys`. Durante el reinicio aparecerá un menú para completar la inscripción de la clave MOK.



## Verificación de carga

Después de completar la inscripción y reiniciar, al insertar `mimodulo.ko` ya no debería aparecer el error anterior. Se puede comprobar la carga con `dmesg`:

```bash
sudo dmesg | tail -n 50
```

Ejemplo de mensajes relevantes:

```
[  195.973677] mimodulo: loading out-of-tree module taints kernel.
[  195.974076] Módulo cargado en el kernel.
```

También es posible consultar información del módulo, como tamaño, usos, dependencias, estado y banderas, mediante:

```bash
cat /proc/modules | grep mimodulo
```

Ejemplo de salida:

```
mimodulo 12288 0 - Live 0x0000000000000000 (O)
```

Que la dirección aparezca como `0x0000000000000000` no implica necesariamente que el módulo se haya cargado en esa dirección; puede ser una limitación de acceso a esa información por motivos de seguridad. Con privilegios de superusuario la salida puede mostrar la dirección real.

Para descargar el módulo:

```bash
sudo rmmod mimodulo
```

Ejemplo de mensaje al descargar:

```
[ 2480.004281] Módulo descargado del kernel.
```


## Información del módulo

Para ver metadatos del módulo:

```bash
modinfo mimodulo.ko
```

![alt text](image.png)

En esa salida se muestran campos como `author`, `description`, `license` y la información de firma. Comparándolo con otro módulo (por ejemplo `des_generic`) pueden observarse diferencias en los campos mostrados, como la presencia de `aliases` o el algoritmo de firma (por ejemplo, `sha512` en las claves del sistema frente a `sha256` usado aquí).


Listado de módulos y módulos no instalados


## Listado de módulos y módulos no instalados

Para generar una lista de módulos cargados actualmente se puede usar `lsmod`:

```bash
sudo lsmod > Modules_Facu.txt
```

Para listar todos los módulos compilados con el kernel y distinguir los que no están cargados, se utilizó el siguiente comando:

```bash
comm -23 <(find /lib/modules/$(uname -r) -type f -name '*.ko*' -exec basename {} \; | sed -e 's/\.ko.*//' -e 's/-/_/g' | sort -u) <(lsmod | awk 'NR>1 {print $1}' | sed 's/-/_/g' | sort -u) > ../../../GITarreros/tp4/Not_installed.txt
```


Consideraciones de seguridad y diferencias con espacio de usuario

Los módulos del kernel tienen privilegios de ejecución más altos que los programas de usuario y pueden afectar significativamente al sistema. Por ello, la firma y verificación de autenticidad de los módulos es importante.

Existen múltiples métodos para firmar binarios ELF: el enfoque usado aquí emplea OpenSSL y la infraestructura MOK, pero también hay técnicas que almacenan la firma en secciones especiales del binario o en archivos externos.

Además, los módulos se ejecutan en un espacio de direcciones (kernel space) distinto al de los programas de usuario (user space). Esta separación protege la integridad del sistema y evita que procesos de usuario afecten directamente al kernel. Los módulos pueden cargar automáticamente controladores al detectar hardware (por ejemplo, mediante udev) y ofrecen APIs que usan programas de usuario.


Herramientas útiles

- `mokutil` — gestión de Machine Owner Keys (MOK).
- `dmesg` — revisar mensajes del kernel.
- `modinfo` — información de módulos.
- `lsmod`, `rmmod`, `insmod` — listar, descargar e insertar módulos.
- `hwinfo` — inspección de hardware (`sudo apt install hwinfo`).

En `HardwareInfo.txt` se incluye un ejemplo de dispositivo utilizado por el grupo.


