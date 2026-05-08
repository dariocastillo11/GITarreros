# TP Práctico: Entorno UEFI, Desarrollo y Análisis de Seguridad

##  Objetivo General

Comprender la arquitectura de **UEFI** como entorno pre-SO, desarrollar binarios nativos, entender su formato y ejecutar rutinas en emuladores (QEMU).

---

## 📋 PARTE 1: Preparación del Entorno (Linux)

### Paso 1.1: Crear Directorio de Trabajo

```bash
mkdir -p uefi_security_lab && cd uefi_security_lab
```



### Paso 1.2: Instalar Dependencias Base

```bash
sudo apt update
sudo apt install -y qemu-system-x86 ovmf gnu-efi build-essential binutils-mingw-w64
```

**Instalamos:**

| Paquete | Para qué sirve |
|---------|----------------|
| `qemu-system-x86` | Emulador de máquina x86 (virtualiza una PC) |
| `ovmf` | Firmware UEFI abierto (es el "BIOS" virtual que usará QEMU) |
| `gnu-efi` | Herramientas para compilar código UEFI en Linux |
| `build-essential` | GCC, Make, etc. (compiladores básicos) |
| `binutils-mingw-w64` | Herramientas para crear ejecutables PE/COFF (formato UEFI) |

**Nota importante:** OVMF es un firmware abierto basado en la especificación UEFI (desarrollado por TianoCore). Cuando ejecutas QEMU con `-bios OVMF.fd`, esa es la "UEFI virtual" de tu máquina emulada.

### Paso 1.3: Instalar Ghidra (Desensambblador)

```bash
sudo apt install -y ghidra || sudo snap install ghidra --classic
```
Ghidra es un desensambblador profesional para analizar binarios y entender código UEFI a nivel de máquina.

---
