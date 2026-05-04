.code16                         # Empezamos en 16 bits (Modo Real)
.global _start

_start:
    cli                         # 1. Desactivamos interrupciones (obligatorio)
    lgdt gdt_descriptor         # 2. Cargamos la tabla GDT

    mov %cr0, %eax              # 3. Activamos el bit de Modo Protegido en CR0
    or $1, %al
    mov %eax, %cr0

    # 4. Salto largo (Far Jump) para entrar a 32 bits
    # 0x08 es el Selector de Código (apunta al segundo descriptor de la GDT)
    ljmp $0x08, $protected_mode

.code32                         # Ahora estamos en 32 bits (Modo Protegido)
protected_mode:
    # 5. Cargamos los registros de segmento con el Selector de Datos (0x10)
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    # 6. ÉXITO VISUAL: Escribimos "XX" en la pantalla (dirección de video 0xb8000)
    movl $0x0f580f58, (0xb8000)

    # 7. PRUEBA DE SEGURIDAD (La consigna del TP):
    # Intentamos escribir en una dirección cualquiera.
    # SI EL DESCRIPTOR 0x10 ES "SOLO LECTURA", ESTO DEBERÍA FALLAR.
    movl $0x11223344, (0x5000)

halt:
    hlt
    jmp halt

# --- TABLA DE DESCRIPTORES GLOBALES (GDT) ---
.align 8
gdt_start:
    .quad 0x0000000000000000    # Descriptor Nulo (obligatorio)

    # Descriptor de Código (Base 0, Límite 4GB, Ejecutable/Lectura)
    # Selector: 0x08
    .quad 0x00cf9a000000ffff

    # Descriptor de Datos (Base 0, Límite 4GB)
    # Selector: 0x10
    # CAMBIO AQUÍ: 0x90 es Solo Lectura | 0x92 es Lectura/Escritura
    .quad 0x00cf9000000ffff     
gdt_end:

gdt_descriptor:
    .word gdt_end - gdt_start - 1
    .long gdt_start