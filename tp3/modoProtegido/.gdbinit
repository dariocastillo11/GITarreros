# Archivo .gdbinit - Configuración automática de GDB
# Coloca este archivo en la carpeta del proyecto

# Configurar arquitectura
set architecture i386

# Conectar a QEMU
target remote :1234

# Esperar a que QEMU esté listo
shell sleep 1

# Pausar la ejecución
interrupt

# Establecer breakpoint en protected_mode (después del salto)
break protected_mode

# Continuar hasta el breakpoint
continue

# Mostrar información de registros
info registers

# Mostrar el código actual
list

# Leer memoria de video
x/4x 0xb8000

# Mensaje de bienvenida
printf "\n=== MODO PROTEGIDO ALCANZADO ===\n"
printf "Usa:\n"
printf "  stepi              - Ejecutar UNA instrucción\n"
printf "  info registers     - Ver registros\n"
printf "  x/4x 0xb8000       - Leer memoria de video\n"
printf "  continue           - Continuar ejecución\n"
printf "  quit               - Salir\n\n"
