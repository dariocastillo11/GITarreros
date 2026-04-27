# suma.s  —  función suma(long a, long b) en AT&T syntax
# Convención System V AMD64 ABI:
#   %rdi = 1er argumento (a)
#   %rsi = 2do argumento (b)
#   %rax = valor de retorno

    .section .text
    .globl  suma       # exportar símbolo para el linker
    .type   suma, @function

suma:
    # Prólogo — no necesitamos frame propio para esta función simple
    movq    %rdi, %rax   # rax = a  (1er argumento)
    addq    %rsi, %rax   # rax = a + b  (2do argumento)
    ret                   # retorna; el caller lee %rax

    .size   suma, .-suma
    