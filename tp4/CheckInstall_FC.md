CheckInstall

Breve descripción

`checkinstall` es una herramienta que rastrea los archivos instalados durante la compilación desde código fuente y genera un paquete `.deb`, `.rpm` (o para otras distribuciones) con el objetivo de poder instalar o desinstalar el software mediante el gestor de paquetes del sistema.

Antes de utilizar `checkinstall` normalmente se ejecuta `./configure` (si aplica) y luego se compila el proyecto con `make`. En lugar de ejecutar `sudo make install`, se usa `sudo checkinstall` para crear e instalar el paquete.

Ejemplo: compilación e instalación de FreeCAD

1) Instalación de herramientas necesarias:

```bash
sudo apt install checkinstall build-essential cmake git
```

2) Descarga de dependencias para FreeCAD:

```bash
sudo add-apt-repository --enable-source ppa:freecad-maintainers/freecad-stable
sudo apt update
sudo apt build-dep freecad
```

3) Clonado del repositorio de FreeCAD:

```bash
git clone --depth 1 https://github.com/FreeCAD/FreeCAD.git
cd FreeCAD
```

4) Configuración y compilación:

```bash
mkdir build
cd build
cmake ..
```

![alt text](image-1.png)

En proyectos grandes es frecuente encontrar múltiples dificultades al compilar, así como dependencias y configuraciones específicas. En este caso la compilación (tras configurar con CMake) se realizó con:

```bash
make -j$(nproc)
```

que utiliza todos los núcleos disponibles. Este proceso puede tardar mucho y presentar numerosos errores; por limitaciones de tiempo no se completó totalmente para este trabajo.

Si la compilación se completa correctamente, la instalación mediante `checkinstall` se realiza con:

```bash
sudo checkinstall
```

La creación del paquete y su instalación pueden visualizarse en otros casos de uso dentro de este trabajo.