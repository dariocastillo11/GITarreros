

gas viene por defecto en binutil. usaremos nasm es parecida pero da un formato asm mas limpio.
instalamos la herramienta.
nasm es un traductor de asembler
```bash
sudo apt update
sudo apt install build-essential nasm gcc-multilib g++-multilib libcurl4-openssl-dev
```

ejemplo asm conectado a c:
```bash
    global sumar_uno ; Hacemos que la función sea visible para C

sumar_uno:
    ; Por convención (System V ABI):
    ; El primer argumento que manda C llega en el registro RDI
    ; El resultado que devolvemos a C debe quedar en el registro RAX
    
    mov rax, rdi    ; Pasamos el número recibido a RAX
    add rax, 1      ; Le sumamos 1
    ret             ; Volvemos a C
```
---
---
compilacion asemble:
```
nasm -f elf64 calculo.asm -o calculo.o
```

---
```bash 
#include <stdio.h>

// Le avisamos a C que existe una función externa llamada sumar_uno
extern long sumar_uno(long n);

int main() {
    long numero = 10;
    long resultado = sumar_uno(numero);
    
    printf("El numero inicial era: %ld\n", numero);
    printf("El resultado de Assembler (n+1) es: %ld\n", resultado);
    
    return 0;
}
```
---
compilacion asemble:
```
nasm -f elf64 calculo.asm -o calculo.o
```
---
---
compilacion c:
```
gcc -c main.c -o main.o
```
---

binarios  .o creados . pero son 2. los uno con:
```
gcc main.o calculo.o -o mi_programa
```
---
ejecuto:
```
./mi_programa
```

---

Paso 6: Conectar Python con C

Para que Python pueda usar tu código de C, no podemos usar un ejecutable común (mi_programa). Necesitamos convertir tu código de C y Assembler en una Librería Compartida (.so), que es como una caja de herramientas que Python puede abrir.



1. Modificar el código de C

Crea un archivo nuevo llamado interfaz.c. Es casi igual al anterior, pero sin el main, porque el "dueño" del programa ahora será Python.


```
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
```
---


2. Compilar como Librería (.so)

Ejecutamos estos comandos para crear libcalculo.so:

```
# 1. Assembler (igual que antes)
nasm -f elf64 calculo.asm -o calculo.o

# 2. C (con el flag -fPIC que es necesario para librerías)
gcc -c -fPIC interfaz.c -o interfaz.o

# 3. Unirlos en una librería dinámica (.so)
gcc -shared interfaz.o calculo.o -o libcalculo.so
```
---

3. El código de Python: app.py

Crea un archivo app.py. Usaremos ctypes para cargar la librería.
```
import ctypes
import os

# 1. Cargar la librería que acabamos de crear
lib_path = os.path.abspath("./libcalculo.so")
lib = ctypes.CDLL(lib_path)

# 2. Configurar los tipos de datos (importante para que no explote)
# Le decimos que procesar_indice recibe un 'long' y devuelve un 'long'
lib.procesar_indice.argtypes = (ctypes.c_long,)
lib.procesar_indice.restype = ctypes.c_long

# 3. Probar la conexión
numero_entrada = 42
print(f"[Python] Enviando {numero_entrada} a la capa C...")

resultado = lib.procesar_indice(numero_entrada)

print(f"[Python] El resultado final es: {resultado}")

```
---
4. Ejecutar la prueba total

En tu terminal:
```
python3 app.py
```