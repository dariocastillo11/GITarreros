#include <stdio.h>

// Función externa en Assembler
extern long sumar(double n);

// Esta función la llamará Python
long procesar_indice(double valor) {
    printf("[C] Recibi el float %f de Python. Llamando a Assembler...\n", valor);
    double res = sumar(valor);
    printf("[C] Assembler respondio %f. Devolviendo a Python...\n", res);
    return res;
}