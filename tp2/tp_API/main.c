#include <stdio.h>

// Le avisamos a C que existe una función externa llamada sumar_uno
extern long sumar(long n);

int main() {
    long numero = 10;
    long resultado = sumar(numero);
    
    printf("El numero inicial era: %ld\n", numero);
    printf("El resultado de Assembler (n+1) es: %ld\n", resultado);
    
    return 0;
}