#include <stdio.h>

// Función externa en Assembler
extern long sumar_uno(double n);

// Esta función la llamará Python
long procesar_indice(double valor) {
    printf("[C] Recibi el float %f de Python. Llamando a Assembler...\n", valor);
    long res = sumar_uno(valor);
    printf("[C] Assembler respondio %ld. Devolviendo a Python...\n", res);
    return res;
}