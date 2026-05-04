#!/bin/bash

# Script para compilar, enlazar y ejecutar con GDB

echo "=== Compilando código avanzado ==="
as -g -o main_avanzado.o main_avanzado.S

echo "=== Enlazando ==="
ld --oformat binary -o protected_avanzado.img -T link.ld main_avanzado.o

echo "=== Verificando con hexdump ==="
hexdump -C protected_avanzado.img | head -20

echo ""
echo "=== Opciones de ejecución ==="
echo "1. Ejecutar sin GDB:"
echo "   qemu-system-i386 -hda protected_avanzado.img"
echo ""
echo "2. Ejecutar CON GDB (debugger):"
echo "   Terminal 1: qemu-system-i386 -hda protected_avanzado.img -s -S"
echo "   Terminal 2: gdb -ex 'target remote :1234' -ex 'continue' main_avanzado.o"
echo ""
echo "✅ Imagen compilada: protected_avanzado.img"
