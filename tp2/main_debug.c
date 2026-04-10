#include <stdio.h>

// Declaramos la función de assembler
extern long sumar_uno(double n);

int main() {
    double valor_test = 42.7;
    printf("--- Iniciando prueba para GDB ---\n");
    long resultado = sumar_uno(valor_test);
    printf("Resultado final: %ld\n", resultado);
    return 0;
}