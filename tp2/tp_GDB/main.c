/* main.c  —  invoca la función suma() implementada en ASM */
#include <stdio.h>

/* Declaración externa: le decimos al compilador que suma()
   existe, pero está definida en otro archivo objeto.       */
extern long suma(long a, long b);

int main(void) {
    long a = 10;
    long b = 25;

    /* Antes de esta línea poner breakpoint en GDB:
       el compilador cargará a→%rdi, b→%rsi          */
    long resultado = suma(a, b);

    printf("suma(%ld, %ld) = %ld\n", a, b, resultado);
    return 0;
}
