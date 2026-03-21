

# 🐧 Laboratorio: Revisión de Linux

### 🎯 Objetivos
* **Parte 2:** Revisar sintaxis de comandos.
* **Parte 3:** Revisar la administración de archivos.
* **Parte 4:** Revisar expresiones regulares.
* **Parte 5:** Revisar la administración del sistema.

---

### 📖 Aspectos básicos / Situación
En este laboratorio, revisará las habilidades básicas de Linux, incluidas la navegación por comandos, la administración de archivos, las expresiones regulares y la administración del sistema. Este laboratorio no es un sustituto de la experiencia anterior de Linux y no cubre necesariamente todas las habilidades de Linux que necesita para este curso. Sin embargo, este laboratorio debe servir como una buena medida de sus habilidades de Linux y ayudarle a dirigirle a donde puede necesitar más revisión.

**💻 Recursos necesarios:**
* Una computadora con el sistema operativo de su elección.

---

## 🛠️ Parte 1: Revisar exploración de sintaxis de comandos
En esta parte, usará los comandos `ls`, `pwd`, `cd` y `sudo` para revisar la navegación básica de sintaxis de comandos.

### Paso 1: Abrir una terminal en el Laboratorio virtual de DEVASC.
* a. Haga doble clic en el ícono de **Emulador de Terminal** en el escritorio para abrir una ventana de terminal.



### Paso 2: Navegar por los directorios.
* **a.** Utilizar el comando `ls` para mostrar el directorio actual. Estos comandos distinguen entre mayúsculas y minúsculas.
    ```bash
    devasc@labvm: ~$ ls
    Descargas de escritorio, Plantillas públicas de música.
    Documentos de laboratorio, fotos instántaneas, vídeos.
    ```
---
**respuesta**:

```bash
dario@dario-N-737R:~$ ls
 clang_format_errors.txt
 cookies.txt
 Descargas
 Documentos
 Escritorio
 horusec
 Imágenes
'kzo-zvna-eez (2021-09-29 at 12_43 GMT-7) [17dheTpiiKeJjBF-eanQgrdjBdjQlTarl].mp4.part'
 MCUXpressoInstaller
 Música
 Plantillas
 pt
 Público
 snap
 Vídeos
 zephyr-sdk-0.17.2
dario@dario-N-737R:~$ 
```
---


* **b.** Utilice el comando `ls` con el argumento `labs` para mostrar el contenido de la carpeta labs.
    ```bash
    devasc @labvm: ~$ ls labs
    devnet-src
    ```
---
**respuesta**:

```bash
dario@dario-N-737R:~$ ls horusec
docker-compose.yml
```
---


* **c.** Utilice el comando `ls` con la opción `-l` para mostrar una "visualización larga" del contenido del directorio actual.
    ```bash
    devasc @labvm: ~$ ls -l
    Total 40.
    drwxr-xr-x 2 devasc devasc 4096 Mar 30 21:25 Escritorio.
    drwxr-xr-x 2 devasc devasc 4096 Abr 15 19:09 Documentos.
    drwxr-xr-x 2 devasc devasc 4096 Abr 15 19:09 Descargas.
    ...
    ```

---
**respuesta**:

```bash
dario@dario-N-737R:~$ ls -l
total 1468
-rw-rw-r--  1 dario dario     105 ago 26  2025  clang_format_errors.txt
-rw-rw-r--  1 dario dario     136 ago 28  2025  cookies.txt
drwxr-xr-x  2 dario dario    4096 mar 18 20:30  Descargas
drwxr-xr-x  3 dario dario    4096 mar 17 10:41  Documentos
drwxr-xr-x  9 dario dario    4096 mar 21 11:28  Escritorio
drwxrwxr-x  2 dario dario    4096 sep 11  2025  horusec
drwxr-xr-x  3 dario dario    4096 ago 21  2025  Imágenes
-rw-rw-r--  1 dario dario 1441298 ago 28  2025 'kzo-zvna-eez (2021-09-29 at 12_43 GMT-7) [17dheTpiiKeJjBF-eanQgrdjBdjQlTarl].mp4.part'
drwxr-xr-x 11 dario dario    4096 ago 22  2025  MCUXpressoInstaller
drwxr-xr-x  2 dario dario    4096 ago 15  2025  Música
drwxr-xr-x  2 dario dario    4096 ago 15  2025  Plantillas
drwxrwxr-x  6 dario dario    4096 mar 17 10:41  pt
drwxr-xr-x  2 dario dario    4096 ago 15  2025  Público
drwx------  9 dario dario    4096 nov 18 08:43  snap
drwxr-xr-x  3 dario dario    4096 ago 25  2025  Vídeos
drwxr-xr-x  4 dario dario    4096 ago 22  2025  zephyr-sdk-0.17.2

```
---



* **d.** Utilice el comando `ls` con la opción `-r` para mostrar el contenido del directorio actual en orden alfabético inverso.

---
**respuesta**:

```bash
dario@dario-N-737R:~$ ls -r
 zephyr-sdk-0.17.2
 Vídeos
 snap
 Público
 pt
 Plantillas
 Música
 MCUXpressoInstaller
'kzo-zvna-eez (2021-09-29 at 12_43 GMT-7) [17dheTpiiKeJjBF-eanQgrdjBdjQlTarl].mp4.part'
 Imágenes
 horusec
 Escritorio
 Documentos
 Descargas
 cookies.txt
 clang_format_errors.txt

```
---

* **e.** Se pueden utilizar varias opciones al mismo tiempo. Utilice el comando `ls` con las opciones `-l` y `-r`.

> [!NOTE]
> **💡 Tip:** Puede usar el comando `man ls` para ver el manual completo o `ls --help` para un resumen corto.


---
**respuesta**:

```bash
dario@dario-N-737R:~$ ls -r -l
total 1468
drwxr-xr-x  4 dario dario    4096 ago 22  2025  zephyr-sdk-0.17.2
drwxr-xr-x  3 dario dario    4096 ago 25  2025  Vídeos
drwx------  9 dario dario    4096 nov 18 08:43  snap
drwxr-xr-x  2 dario dario    4096 ago 15  2025  Público
drwxrwxr-x  6 dario dario    4096 mar 17 10:41  pt
drwxr-xr-x  2 dario dario    4096 ago 15  2025  Plantillas
drwxr-xr-x  2 dario dario    4096 ago 15  2025  Música
drwxr-xr-x 11 dario dario    4096 ago 22  2025  MCUXpressoInstaller
-rw-rw-r--  1 dario dario 1441298 ago 28  2025 'kzo-zvna-eez (2021-09-29 at 12_43 GMT-7) [17dheTpiiKeJjBF-eanQgrdjBdjQlTarl].mp4.part'
drwxr-xr-x  3 dario dario    4096 ago 21  2025  Imágenes
drwxrwxr-x  2 dario dario    4096 sep 11  2025  horusec
drwxr-xr-x  9 dario dario    4096 mar 21 11:28  Escritorio
drwxr-xr-x  3 dario dario    4096 mar 17 10:41  Documentos
drwxr-xr-x  2 dario dario    4096 mar 18 20:30  Descargas
-rw-rw-r--  1 dario dario     136 ago 28  2025  cookies.txt
-rw-rw-r--  1 dario dario     105 ago 26  2025  clang_format_errors.txt
```
---
---

* **f.** Hay muchas más opciones que se pueden usar con el comando ls. Utilice el comando man con el
argumento ls para ver todas las posibilidades en el manual. El comando man se puede usar para buscar
cualquier comando dentro del sistema. Utilice la barra espaciadora para avanzar a pantallas posteriores.
Presione q para salir..

```bash 
devasc @labvm: ~$ man ls
```
(La línea de comandos desaparece y se abre la página de manual de ls.)
LS (1) Comandos de usuario LS (1)
NOMBRE
ls - lista el contenido del directorio
SINÓPSIS
ls [OPCIÓN]... [ARCHIVO]...
DESCRIPCIÓN
Lista de información acerca de los DOCUMENTOS (el directorio actual
predeterminado).

Ordenar entradas alfabéticamente si ninguna es de-cftuvSUX nor--tipo especial.
fied.
Los argumentos obligatorios para las opciones largas son obligatorios para las
opciones cortas.
too.
-a, —all
No ignorar las entradas que comienzan con:
-A, —almost all
No enumerar implícitos. and..
-Autor
Página de manual ls (1) línea 1 (pulse h para obtener ayuda o q para salir)


* **g.** También puede usar el argumento —help después de la mayoría de los comandos para ver un resumen
más corto de todas las opciones de comando disponibles.
    ```bash
   devasc @labvm: ~$ ls —help

    ```
   Uso: ls [OPCIÓN]... [ARCHIVO]...
    Lista de información acerca de los DOCUMENTOS (el directorio actual predeterminado).
    Ordenar las entradas alfabéticamente si no se especifica -cftuvSUX ni.
    Los argumentos obligatorios de las opciones largas también son obligatorios para las
    opciones cortas.
    -a, —all do not ignore entries starting with (no ignora las entradas que empiecen
    por)
    -A, --almost-all do not list implied . and .. (—casi todos no se enumeran
    implícitos. y..)
    (Salida Omitida)
    devasc@labvm:~$ 
---


* **h.** Use el comando `pwd` para desplegar el directorio actual.
    ```bash
    devasc @labvm: ~$ pwd
    /home/devasc
    ```
---
**respuesta**:

```bash
dario@dario-N-737R:~$ pwd
/home/dario
```
---



* **i.** Utilice el comando `cd` para cambiar el directorio a `/home/devasc/documents`.
---
**respuesta**:

```bash
dario@dario-N-737R:~$ cd horusec/
dario@dario-N-737R:~/horusec$ 
```
---

* **j.** Utilice el comando `cd` con el símbolo `/` para cambiar al directorio raíz.
---
**respuesta**:

```bash
dario@dario-N-737R:~/horusec$ cd /
dario@dario-N-737R:/$ 
```
---
---



* **k.** Vuelva al directorio /home/devasc/documents. Consejo: Puede mover un directorio a la vez o todo el
camino a un destino. Para ingresar rápidamente el comando, escriba las primeras letras del nombre del
directorio y presione Tab para que el sistema introduzca automáticamente el resto del nombre. Recuerde
que los nombres distinguen entre letras mayúsculas y minúsculas.

```bash
devasc @labvm: /$ cd /home/devasc/documents/
9devasc@labvm:~/Documents$
```

---

* **l.** Use los caracteres `..` para subir un solo directorio.
---
**respuesta**:

```bash
dario@dario-N-737R:/$ cd proc/
dario@dario-N-737R:/proc$ cd ..
dario@dario-N-737R:/$ 
```
---

### Paso 3: Utilice comandos de superusuario.
* **a.** Utilice el comando `sudo` para emitir un solo comando como usuario root.
    ```bash
    devasc @labvm: ~$ sudo apt-get update
    ```

---
**respuesta**:

```bash
dario@dario-N-737R:/$ sudo apt-get update
[sudo] contraseña para dario: 
Lo siento, pruebe otra vez.
[sudo] contraseña para dario: 
Des:1 https://download.docker.com/linux/ubuntu noble InRelease [48,5 kB]
Des:2 https://repo.steampowered.com/steam stable InRelease [3.622 B]           
Des:3 https://download.docker.com/linux/ubuntu noble/stable amd64 Packages [47,2 kB]

---
---
Des:45 http://archive.ubuntu.com/ubuntu noble-backports/universe amd64 Components [13,1 kB]
Des:46 http://archive.ubuntu.com/ubuntu noble-backports/multiverse amd64 Components [212 B]
Descargados 17,8 MB en 6s (2.947 kB/s)                                         
Leyendo lista de paquetes... Hecho
dario@dario-N-737R:/$ 

```
---

---

## 📂 Parte 2: Revisión de Administración de Archivos

En esta parte, revisará los permisos de archivos, cambiará los permisos y la propiedad de archivos, moverá
archivos, copiará archivos, eliminará archivos y verá archivos.

### Paso 1: Revisión de permisos de archivos.

* **a.** Utilice ls Desktop -l para mostrar el contenido de la carpeta Escritorio.

```bash
devasc @labvm: ~$ ls Desktop -l
Total 28.
-rwxr-xr-x 1 devasc devasc 1095 Mar 30 21:24 chromium_chromium.desktop

-rwxr-xr-x 1 devasc devasc 401 Mar 30 21:25 cisco-packet-tracer_cisco-pacet-
tracer.desktop

-rwxr-xr-x 1 devasc devasc 776 Mar 30 21:23 code.desktop
-rwxr-xr-x 1 devasc 373 Mar 30 21:25 drawio_drawio.desktop
-rwxr-xr-x 1 devasc devasc 250 Mar 30 21:21 exo-terminal-emulator.desktop
-rwxr-xr-x 1 devasc 99 Mar 30 21:21 labs.desktop
-rwxr-xr-x 1 devasc 334 Mar 30 21:24 postman_postman.desktop
devasc@labvm:~$

```

---
* **b.** Responda a las siguientes preguntas sobre la salida anterior. Si es necesario, busque en Internet la
información del permiso del archivo Linux que se muestra en la salida del comando ls.

| Pregunta | Respuesta |
| :--- | :--- |
| ¿Qué representa el guion inicial? | Este es el campo de tipo de archivo. El guion representa un archivo normal. |
| ¿Qué habría si fuera un directorio? | Sería una "d" para "directorio". |
| ¿Qué representan las 3 letras siguientes? | Los permisos del **propietario** del archivo. |
| ¿Qué representan las 3 letras intermedias? | Los permisos del **grupo** sobre el archivo. |
| ¿Qué representan las 3 últimas letras? | Los permisos que **otros usuarios** tienen. |
| ¿Qué significa "r"? | Permiso de "leer" (read). |
| ¿Qué significa "w"? | Permiso de "escribir" (write). |
| ¿Qué significa "x"? | Permiso de "ejecutar" (execute). |

### Paso 2: Cambiar los permisos y la propiedad.
1.  **Crear script:** `echo "ls ../Desktop " > myfile.sh`
---
**respuesta**:

```bash
dario@dario-N-737R:~/Escritorio$ echo "ls ..Desktop" > myfile.sh
```
---

2.  **Ver contenido:** `cat myfile.sh`
---
**respuesta**:

```bash
dario@dario-N-737R:~/Escritorio$ cat myfile.sh 
ls ..Desktop
```
---
3.  **Ejecutar:** `./myfile.sh` (Dará permiso denegado inicialmente).

---
**respuesta**:
```bash
dario@dario-N-737R:~/Escritorio$ ./myfile.sh
bash: ./myfile.sh: Permiso denegado
```
---

4.  **Dar permisos:** `chmod +x myfile.sh`

---
**respuesta**:
```bash
dario@dario-N-737R:~/Escritorio$ chmod +x myfile.sh
```
---

5.  **Cambiar dueño:** `sudo chown root myfile.sh`

---
**respuesta**:
```bash
dario@dario-N-737R:~/Escritorio$ sudo chown root myfile.sh
[sudo] contraseña para dario: 
```
---

### Paso 3, 4 y 5: Mover, Copiar y Remover.
* **Mover:** `mv myfile.sh /Home/Devasc/Desktop/`

---
**respuesta**:
```bash
dario@dario-N-737R:~/Escritorio$ ls
 eclypsium                            myfile.sh              SistemaOperativo
'gestion de la calidad del sofware'   RedesDeComputacion     SOII
 gestionDeLasOrganizaciones           SistemaDeComputacion   steam.desktop
dario@dario-N-737R:~/Escritorio$ mv myfile.sh SistemaDeComputacion/
dario@dario-N-737R:~/Escritorio$ ls
 eclypsium                            RedesDeComputacion     SOII
'gestion de la calidad del sofware'   SistemaDeComputacion   steam.desktop
 gestionDeLasOrganizaciones           SistemaOperativo
dario@dario-N-737R:~/Escritorio$ ls SistemaDeComputacion/
myfile.sh  SistemaDeComputacion
dario@dario-N-737R:~/Escritorio$ ls
 eclypsium                            RedesDeComputacion     SOII
'gestion de la calidad del sofware'   SistemaDeComputacion   steam.desktop
 gestionDeLasOrganizaciones           SistemaOperativo
dario@dario-N-737R:~/Escritorio$ 

```
---

* **Renombrar:** `mv myfile.sh myfile_renamed.sh`

---
**respuesta**:
```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ ls
myfile.sh  SistemaDeComputacion
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ mv myfile.sh myfile_renamed.sh 
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ ls
myfile_renamed.sh  SistemaDeComputacion
```
---

* **Copiar:** `cp myfile_renamed.sh myfile_renamed_and_copied.sh`

---
**respuesta**:
```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ ls
myfile_renamed.sh  SistemaDeComputacion
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ cp myfile_renamed.sh myfile_renamed_and_copied.sh
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ ls
myfile_renamed_and_copied.sh  myfile_renamed.sh  SistemaDeComputacion
```
---

* **Remover:** `rm myfile_renamed_and_copied.sh`

---
**respuesta**:
```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ ls
myfile_renamed_and_copied.sh  myfile_renamed.sh  SistemaDeComputacion
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ rm myfile_renamed_and_copied.sh
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ ls
myfile_renamed.sh  SistemaDeComputacion
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ 
```
---

### Paso 6: Redirección de salida.
* `>` : Colocar texto en un nuevo archivo (sobrescribe).
* `>>` : Anexar texto al final del archivo.



---
**respuesta**:
```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ cat myfile_renamed.sh 
ls ..Desktop
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ echo "hola somos equipo GITarreros" >> myfile_renamed.sh 
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ cat myfile_renamed.sh 
ls ..Desktop
hola somos equipo GITarreros
```
---

---
**respuesta**:
```bash

dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ echo "hola" > myfile_renamed.sh 
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ cat myfile_renamed.sh 
hola
```
---
---
### Paso 7: Utilice el editor de texto vim.
**a**. Utilice el siguiente comando para iniciar el editor de texto vi y abrir un archivo de texto.
```
devasc @labvm: ~$ vim linux2.txt
```
En la ventana del editor se muestra el siguiente contenido:
¡Linux es IMPRESIONANTE!
¡Me encanta Linux!

---


**b**. Utilice el editor de texto para cambiar el contenido a lo siguiente:
Linux es Linux.
¡Soy IMPRESIONANTE!
La tecla insert le permitirá entrar en el modo de edición, añadiendo después de la posición del cursor,
mientras que la tecla i le permitirá entrar en el modo de edición, insertando en la posición del cursor.
Tiene que usar la tecla Esc para entrar en el modo de comando para moverse. Recuerde que d eliminará
(cortará), y tirará (copiará), y p pondrá (pegará) la línea actual con el cursor.

---


**c.*** Guarde el texto en un nuevo archivo llamado "linux3.txt". Recuerde que tiene que estar en el modo de
comando y escribir dos puntos ( : ) para entrar en modo ex para que pueda escribir (guardar) el
documento :w linux3.txt). A continuación, puede usar el comando quit (exit) :q )para salir del editor vi.

---


**d.** Use el comando cat para ver el contenido del archivo linux3.txt.
```
devasc @labvm: ~$ cat linux3.txt
```
Linux es Linux
¡Soy IMPRESIONANTE!
devasc@labvm:~$
Pueden jugar un poco en https://www.openvim.com/
---


---


## 🔍 Parte 3: Revisión de Expresiones Regulares
Uso del comando `grep` para filtrar.

| Comando | Función |
| :--- | :--- |
| `grep devasc /etc/passwd` | Busca la palabra "devasc". |
| `grep '^root' /etc/passwd` | Busca "root" al **principio** de la línea. |
| `grep 'false$' /etc/passwd` | Busca "false" al **final** de la línea. |
| `grep 'd.. m' /etc/passwd` | Coincide con palabras de longitud específica (comodín `.`). |
| `grep '[8-9]' /etc/passwd` | Busca líneas que contengan números del 8 al 9. |
| `grep 'new*' /etc/passwd` | Busca apariciones de cero o más del patrón precedente. |

---
---
**respuesta**:
```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ grep devasc /etc/passwd

dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ grep '^root' /etc/passwd  

    root:x:0:0:root:/root:/bin/bash

dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ grep 'false$' /etc/passwd 

    dhcpcd:x:100:65534:DHCP Client Daemon,,,:/usr/lib/dhcpcd:/bin/false
    tss:x:105:105:TPM software stack,,,:/var/lib/tpm:/bin/false
    whoopsie:x:107:109::/nonexistent:/bin/false
    speech-dispatcher:x:111:29:Speech Dispatcher,,,:/run/speech-dispatcher:/bin/false
    hplip:x:116:7:HPLIP system user,,,:/run/hplip:/bin/false
    gnome-initial-setup:x:119:65534::/run/gnome-initial-setup/:/bin/false
    gdm:x:120:121:Gnome Display Manager:/var/lib/gdm3:/bin/false
    clamav:x:125:128::/var/lib/clamav:/bin/false

dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ grep 'd.. m' /etc/passwd  

dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ grep '[8-9]' /etc/passwd  

    mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
    news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
    list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin
    irc:x:39:39:ircd:/run/ircd:/usr/sbin/nologin
    systemd-network:x:998:998:systemd Network Management:/:/usr/sbin/nologin
    systemd-timesync:x:996:996:systemd Time Synchronization:/:/usr/sbin/nologin
    systemd-resolve:x:991:991:systemd Resolver:/:/usr/sbin/nologin
    systemd-oom:x:990:990:systemd Userspace OOM Killer:/:/usr/sbin/nologin
    whoopsie:x:107:109::/nonexistent:/bin/false
    dnsmasq:x:999:65534:dnsmasq:/var/lib/misc:/usr/sbin/nologin
    avahi:x:108:111:Avahi mDNS daemon,,,:/run/avahi-daemon:/usr/sbin/nologin
    tcpdump:x:109:112::/nonexistent:/usr/sbin/nologin
    speech-dispatcher:x:111:29:Speech Dispatcher,,,:/run/speech-dispatcher:/bin/false
    fwupd-refresh:x:989:989:Firmware update daemon:/var/lib/fwupd:/usr/sbin/nologin
    gnome-remote-desktop:x:988:988:GNOME Remote Desktop:/var/lib/gnome-remote-desktop:/usr/sbin/nologin
    polkitd:x:987:987:User for polkitd:/:/usr/sbin/nologin
    rtkit:x:117:119:RealtimeKit,,,:/proc:/usr/sbin/nologin
    colord:x:118:120:colord colour management daemon,,,:/var/lib/colord:/usr/sbin/nologin
    gnome-initial-setup:x:119:65534::/run/gnome-initial-setup/:/bin/false
    clamav:x:125:128::/var/lib/clamav:/bin/false

dario@dario-N-737R:~/Escritorio/SistemaDeComputacion$ grep 'new*' /etc/passwd   

    news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
    _apt:x:42:65534::/nonexistent:/usr/sbin/nologin
    nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
    systemd-network:x:998:998:systemd Network Management:/:/usr/sbin/nologin
    messagebus:x:101:101::/nonexistent:/usr/sbin/nologin
    syslog:x:102:102::/nonexistent:/usr/sbin/nologin
    kernoops:x:106:65534:Kernel Oops Tracking Daemon,,,:/:/usr/sbin/nologin
    whoopsie:x:107:109::/nonexistent:/bin/false
    tcpdump:x:109:112::/nonexistent:/usr/sbin/nologin
    cups-pk-helper:x:112:114:user for cups-pk-helper service,,,:/nonexistent:/usr/sbin/nologin
    saned:x:113:116::/var/lib/saned:/usr/sbin/nologin
    cups-browsed:x:115:114::/nonexistent:/usr/sbin/nologin
```


---

# ⚙️ Parte 4: Revisión del Sistema de Administración

En esta parte, revise las tareas básicas de administración del sistema Linux, incluyendo el apagado del equipo, ver y probar la configuración de red, vigilar procesos, administrar paquetes de instalación, actualizar contraseñas de usuario, agregar contenido a archivos y usar editores de texto.

---

### 🛑 Paso 1: Apague la computadora.

* **a.** Utilice el comando `shutdown now` para iniciar un apagado del sistema operativo (y la máquina virtual) inmediatamente. No tiene que realizar esta acción, ya que la máquina virtual se apagará y tendrá que reiniciarla manualmente. Los formatos de este argumento de tiempo pueden ser la palabra **now**, una hora del día en el formato **hh:mm** o el número de minutos a retrasar en el formato **+minutes**.
    ```bash
    devasc @labvm: ~$ shutdown now
    ```

* **b.** Utilice el comando `date` para comprobar la fecha establecida del sistema operativo.
    ```bash
    devasc @labvm: ~$ date
    vie 17 abr 2020 08:53:20 UTC
    devasc@labvm:~$
    ```

* **c.** Utilice el comando `shutdown +1 “¡Vuelva pronto!"` para apagar el sistema operativo en un minuto y mostrar el mensaje "¡Vuelva pronto!" Asegúrese de cancelar o su máquina virtual se apagará.
    ```bash
    devasc @labvm: ~$ shutdown+1 "¡Vuelta pronto!"
    Cierre programado para vie 2020-04-17 20:57:13 UTC, use 'shutdown -c' para cancelar.
    devasc @labvm: ~$ shutdown -c
    devasc@labvm:~$
    ```

---

### 🌐 Paso 2: Ver y probar la configuración de red.



* **a.** Utilice el comando `ip address` para mostrar la configuración de red. La salida es un poco más detallada. Por ejemplo, observe que se muestran cinco direcciones IPv4 para la interfaz **dummy0**.
    ```text
    devasc @labvm: ~$ ip address
    1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00 brd 00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
    ...
    2: enp0s3: <BROADCAST, MULTICAST, UP, LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/éter 08:00:27:ce:2b:8b brd ff:ff:ff:ff:ff:ff
    inet 10.0.2.15/24 brd 10.0.2.255 scope global dynamic enp0s3
    ...
    3: dummy0: <BROADCAST, NOARP, UP, LOWER_UP> mtu 1500 qdisc noqueue state UNKONWN group default qlen 1000
    link/éter 46:8 b:41:b5:de:aa brd ff:ff:ff:ff:ff:ff
    Inet 192.0.2.1/32 scope global dummy0
    Inet 192.0.2.2/32 scope global dummy0
    Inet 192.0.2.3/32 scope global dummy0
    Inet 192.0.2.4/32 scope global dummy0
    Inet 192.0.2.5/32 scope global dummy0
    ```

* **b.** Utilice el comando `ping` con las opciones `-c 4` para hacer ping a un equipo de la red local cuatro veces. Debe utilizar una dirección IP válida de un dispositivo en su red local.
    ```bash
    devasc @labvm: ~$ ping -c 4 192.168.1.1
    PING 192.168.1.1 (192.168.1.1) 56(84) bytes de datos.
    64 bytes from 192.168.1.1: icmp_seq=1 ttl=63 time=1.13 ms
    ...
    4 paquetes transmitidos, 4 recibidos, 0% paquetes pérdidos, tiempo 3005ms
    ```

* **c.** También puede hacer ping a un nombre y el **Sistema de nombres de dominio (DNS)** resolverá el nombre en una dirección IP.
    ```bash
    devasc @labvm: ~$ ping -c 4 www.cisco.com
    PING e2867.dsca.akamaiedge.net (23.204.11.200) 56(84) bytes de datos.
    ...
    4 paquetes transmitidos, 4 recibidos, 0% paquetes perdidos, tiempo 3007ms.
    ```

---

### 📊 Paso 3: Ver procesos.

* **a.** Utilice el comando `ps` para mostrar los procesos que se están ejecutando en la terminal actual.
* **b.** Utilice el comando `ps` con la opción `-e` para mostrar todos los procesos que se ejecutan en el equipo.
* **c.** Puede canalizar cualquier salida de comando a una pantalla a la vez agregando `| more`. Se muestra una pantalla de salida con el **—more—** que se muestra en la parte inferior.
    ```bash
    devasc @labvm: ~$ ps -e | more
    ```
* **d.** Utilice el comando `ps` con la opción `-ef` para mostrar con más detalle todos los procesos.

---

### 📦 Paso 4: Administrar paquetes.

* **a.** Utilice el comando `apt-get update` para actualizar la lista de paquetes disponibles en el sistema operativo. Debe utilizar permisos de nivel administrativo.
    ```bash
    devasc @labvm: ~$ sudo apt-get update
    ```

* **b.** Utilice el comando `apt-cache search` para encontrar un paquete específico.
    ```bash
    devasc@labvm:~$ apt-cache search speed test
    ```

* **c.** Utilice el comando `apt-get install` para instalar un paquete.
    ```bash
    devasc @labvm: ~$ sudo apt-get install speedtest-cli
    ```

* **d.** Ahora puede usar el comando `speedtest-cli` para probar su velocidad actual de conexión a Internet.
    ```text
    Descargar: 90.87 Mbit/s
    Carga: 17.87 Mbit/s
    ```

* **e.** Utilice el comando `apt-get upgrade` para actualizar todos los paquetes y dependencias del equipo.
* **f.** Utilice el comando `apt-get purge` para eliminar completamente un paquete del equipo.

---

### 🔑 Paso 5: Actualizar Contraseñas.

* **a.** Utilice el comando `passwd` para actualizar su contraseña.
* **b.** Utilice el comando `passwd` con la opción `-S` para ver el estado de su contraseña.
    ```bash
    devasc @labvm: ~$ passwd -S
    devasc P 04/17/2020 0 99999 7 -1
    ```

* **c.** Utilice las páginas de manual para el comando passwd (`man passwd`) para investigar la opción `-S` y encontrar la respuesta a las siguientes preguntas.

> [!IMPORTANT]
> **Preguntas:**
>
> * **¿Cuál es el estado actual de la contraseña?**
>   * P indica una contraseña utilizable.
> * **¿Cuál es el número mínimo de días que deben pasar antes de que se pueda cambiar la contraseña?**
>   * 0
> * **¿Cuál es el número de días después de la expiración de la contraseña que la cuenta permanece activa?**
>   * -1 indica que la contraseña nunca caduca debido a la inactividad.

---
