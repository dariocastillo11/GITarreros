#include <stdio.h>

// Función externa en Assembler
extern long sumar_uno(long n);

// Esta función la llamará Python
long procesar_indice(long valor) {
    printf("[C] Recibi el valor %ld de Python. Llamando a Assembler...\n", valor);
    long res = sumar_uno(valor);
    printf("[C] Assembler respondio %ld. Devolviendo a Python...\n", res);
    return res;
}