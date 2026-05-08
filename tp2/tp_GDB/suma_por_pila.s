# suma_por_pila.s  —  función suma_por_pila() en AT&T syntax
#
# Según System V AMD64 ABI, cuando se pasan más de 6 parámetros, los restantes van a la pila.
# Nosotros pasamos 8 parámetros desde C (main2.c):
# Parámetros 1 al 6 (los que pasamos como 0) -> van a registros (%rdi, %rsi, %rdx, %rcx, %r8, %r9) y los ignoramos por completo.
# Parámetro 7 (a = 10)  -> 16(%rbp)
# Parámetro 8 (b = 25)  -> 24(%rbp)

    .section .text
    .globl  suma_por_pila    # exportamos el símbolo para que gcc lo pueda enlazar
    .type   suma_por_pila, @function

suma_por_pila:
    # ------------------ PRÓLOGO ------------------
    # Preparamos el propio stack frame de la función
    pushq   %rbp             # Guardamos el puntero base del "caller" (main)
    movq    %rsp, %rbp       # Adoptamos el puntero base actual para nosotros
    
    # ------------------ MAPA DE LA PILA (Stack Frame) ------------------
    # Visto desde %rbp este es el panorama:
    # 24(%rbp) -> 8vo parámetro que mandó C (b)
    # 16(%rbp) -> 7mo parámetro que mandó C (a)
    #  8(%rbp) -> Dirección de retorno automático de la instrucción CALL
    #  0(%rbp) -> Valor original de %rbp (puesto por el pushq arriba)
    
    # ------------------ CUERPO ------------------
    # Leemos directamente de la memoria de la pila, es decir del 'stackframe', ignorando los registros
    movq    16(%rbp), %rax   # Ponemos el argumento 'a' (10) en %rax
    addq    24(%rbp), %rax   # Le sumamos el argumento 'b' (25) en %rax

    # ------------------ EPÍLOGO ------------------
    # Restauramos la pila para no romper el programa al volver al main
    popq    %rbp
    ret                      # Regresamos a C. Como manda la norma, el resultado ya está en %rax.

    .size   suma_por_pila, .-suma_por_pila
