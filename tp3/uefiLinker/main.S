.code16                         # Indica que usamos modo real de 16 bits
.global _start

_start:
    mov $msg, %si               # Carga la dirección del mensaje en SI
    mov $0x0e, %ah              # Función BIOS 0x0E: escribir carácter en modo teletipo
loop:
    lodsb                       # Carga el siguiente byte de (%si) en %al e incrementa %si
    or %al, %al                 # ¿Es el byte nulo (0)?
    jz halt                     # Si es cero, terminamos
    int $0x10                   # Llama a la interrupción de video de la BIOS
    jmp loop                    # Repite para el siguiente carácter
halt:
    hlt                         # Detiene la CPU hasta la próxima interrupción

msg:
    .ascii "GITarreros OS v1.0 - 2026"
    .byte 13, 10                # Salto de línea: CR (13) y LF (10)
    .ascii "Prof: Javier Jorge Castillo, Suarez, Martinez Oprima"
    .byte 13, 10                # Otro salto de línea
    .ascii "Presione una tecla para iniciar..."
    .byte 0                     # Carácter nulo para marcar el fin del texto