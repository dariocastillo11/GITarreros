.code16
.global _start

_start:
    cli                         # 1. Desactivar interrupciones
    lgdt gdt_descriptor         # 2. Cargar la tabla GDT

    mov %cr0, %eax              # 3. Setear el bit PE (Protection Enable)
    or $1, %al
    mov %eax, %cr0

    # 4. Salto largo para limpiar el pipeline y cargar CS con el selector de código
    ljmp $0x08, $protected_mode

.code32
protected_mode:
    # 5. Cargar registros de datos con el selector de datos (0x10)
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss

    # Cargar ESP para la pila
    mov $0x90000, %esp

    # ============================================
    # PRUEBA 1: Escribir en memoria de video
    # (Segmento de código permite lectura/escritura)
    # ============================================
    movl $0x0f4f0f4f, (0xb8000)    # Escribe "OO" en color blanco
    movl $0x0f4b0f6b, (0xb8004)    # Escribe "kK"

    # ============================================
    # PRUEBA 2: Intentar escribir en segmento READ-ONLY
    # (Si funciona, segmento es writable)
    # (Si falla, genera General Protection Fault #GP)
    # ============================================
    
    # Cargar el selector de datos de solo lectura (0x18)
    mov $0x18, %ax
    mov %ax, %ds

    # Intentar escribir en dirección de datos
    mov $0x0f580f58, %eax          # Valor a escribir ('XX')
    movl %eax, (0xc0000)           # ESTO DEBERÍA FALLAR si es read-only

    # Si llegamos aquí, el segmento NO es read-only (error en la consigna)
    movl $0x0f450f45, (0xb8008)    # Escribir "EE" en verde si tuvo éxito

halt:
    hlt
    jmp halt

# --- Estructura de la GDT ---
.align 8
gdt_start:
    .quad 0x0000000000000000    # Descriptor nulo (obligatorio)

    # Descriptor de Código (Base 0x00000000, Límite 4GB, Ejecutable/Lectura/Escritura)
    # Selector: 0x08
    .quad 0x00cf9a000000ffff

    # Descriptor de Datos (Base 0x00100000, Límite 1MB, Lectura/Escritura)
    # Selector: 0x10
    # Base: 0x00100000, Límite: 0x00FFF (1MB), Presente, DPL=0, Lectura/Escritura
    .byte 0xff              # Límite bajo
    .byte 0x0f              # Límite alto
    .byte 0x00              # Base 0
    .byte 0x10              # Base 1
    .byte 0x00              # Base 2
    .byte 0x92              # Presente, DPL=0, Lectura/Escritura, Acceso NO es código
    .byte 0xcf              # Granularidad 4KB, Límite bits altos
    .byte 0x00              # Base 3

    # Descriptor de Datos READ-ONLY (Base 0x00200000, Límite 1MB, SOLO LECTURA)
    # Selector: 0x18
    # Base: 0x00200000, Límite: 0x00FFF (1MB), Presente, DPL=0, SOLO LECTURA (0x90)
    .byte 0xff              # Límite bajo
    .byte 0x0f              # Límite alto
    .byte 0x00              # Base 0
    .byte 0x20              # Base 1 (0x00200000 >> 16)
    .byte 0x00              # Base 2
    .byte 0x90              # Presente, DPL=0, SOLO LECTURA (cambio de 0x92 a 0x90)
    .byte 0xcf              # Granularidad 4KB, Límite bits altos
    .byte 0x00              # Base 3
gdt_end:

gdt_descriptor:
    .word gdt_end - gdt_start - 1
    .long gdt_start

# Rellenar hasta 512 bytes con la firma de boot
.org 0x1fe
.short 0xaa55
