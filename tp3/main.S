.code16
.global _start

_start:
    # 1. Forzar que los segmentos de memoria sean 0
    cli                         # Desactiva interrupciones
    xor %ax, %ax
    mov %ax, %ds
    mov %ax, %es
    sti                         # Activa interrupciones

    # 2. Poner la pantalla en modo color (limpia la pantalla)
    mov $0x03, %ax              # Modo texto 80x25 color
    int $0x10

    # 3. Cambiar color de fondo (Divertido: Pantalla azul/verde)
    mov $0x0600, %ax            # Función scroll
    mov $0x1F, %bh              # Fondo Azul (1), Letra Blanca (F)
    mov $0x0000, %cx            # Esquina superior izquierda
    mov $0x184f, %dx            # Esquina inferior derecha
    int $0x10

    mov $msg, %si
    mov $0x0e, %ah              # Función teletipo de BIOS
loop:
    lodsb                       # Carga AL con el byte en DS:SI y avanza SI
    or %al, %al                 # ¿Es el fin del string (0)?
    jz halt
    int $0x10                   # Imprime el carácter
    jmp loop

halt:
    # Hacer que el cursor parpadee al final para saber que terminó
    jmp halt

msg:
    .asciz ">>> SISTEMA GITarreros BOOTING... Facundo, Dario, JOaquin: HELLO WORLD! <<<"