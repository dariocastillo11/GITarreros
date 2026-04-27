Objetivo General: Comprender la arquitectura de la Interfaz de Firmware Extensible Unificada (UEFI) como un entorno pre-sistema operativo, desarrollar binarios nativos, entender su formato y ejecutar rutinas tanto en entornos emulados como en hardware físico (bare metal).

Para llevar a cabo este trabajo practico primero debemos contar con las siguientes herramientas instaladas:
QEMU: herramienta open source para emulacion de arquitecturas de hardware y virtualizacion de sistemas operativos.

OVMF: herramienta de firmware que permite el uso de UEFI en vez de legacy BIOS en QEMU

GNU-EFI: herramienta de cross compilacion que permite usar el compilador gcc tradicional para generar binarios EFI.

GHIDRA: nos permite hacer ingenieria inverza sobre los binarios de uefi con el fin de decompilarlos, llevandolo a codigo legible por humanos.


1- En una primera instancia se genera el directorio de trabajo 
 mkdir -p ~/uefi_security_lab && cd ~/uefi_security_lab

2- se instalan las dependencias base:
sudo apt install -y qemu-system-x86 ovmf gnu-efi build-essential binutils-mingw-w64

sudo apt install -y ghidra || sudo snap install ghidra --classic

Arranque en el entorno virtual:
Uefi: entorno completo con su propio gestor de memoria, red y consola

qemu-system-x86_64 -m 512 -bios /usr/share/ovmf/OVMF.fd -net none

pasted imag.pngprin

1.2 Exploración de Dispositivos (Handles y Protocolos)
UEFI no usa letras de unidad fijas (como C:). Mantiene una base de datos de "Handles" (identificadores) que agrupan "Protocolos" (interfaces de software como SIMPLE_FILE_SYSTEM).
Comandos en la UEFI Shell:
Plaintext
Shell> map
Shell> FS0:
FS0:\> ls
Shell> dh -b

Razonamiento 1:  En BIOS las direcciones de entrada y salida de hardware debian estar preestablecidas por lo que un cambio en esto puede llevar a fallos en software de por ejemplo el bootloader. En el caso de UEFI se utilizan protocolos, se crea un Handle ID asociado a cada componente y se buscan bloques especificos dentro de estos para determinar su funcionamiento. En el caso de un disco duro, UEFI buscara un bloque de arranque dentro del mismo, por lo que no importa si es una ssd o hdd, uefi utilizara la imagen de sistema operativo extraida de un dispositivo con ese bloque en especifico. De esta forma tambien podemos proteger el sistema de ataques de otros componentes si estos no cuentan con el bloque necesario para booteo y comandos necesarios para UEFI. Los protocolos deben tener una firma digital verificable por uefi para poder ser cargados, de no ser asi son ignorados. 