

gas viene por defecto en binutil. usaremos nasm es parecida pero da un formato asm mas limpio.
instalamos la herramienta.
nasm es un traductor de asembler
```bash
sudo apt update
sudo apt install build-essential nasm gcc-multilib g++-multilib libcurl4-openssl-dev
```

ejemplo asm conectado a c:
```c++
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
```bash
nasm -f elf64 calculo.asm -o calculo.o
```

---
```c++
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
```bash
nasm -f elf64 calculo.asm -o calculo.o
```
---
---
compilacion c:
```bash
gcc -c main.c -o main.o
```
---

binarios  .o creados . pero son 2. los uno con:
```bash
gcc main.o calculo.o -o mi_programa
```
---
ejecuto:
```bash
./mi_programa
```

---

Paso 6: Conectar Python con C

Para que Python pueda usar tu código de C, no podemos usar un ejecutable común (mi_programa). Necesitamos convertir tu código de C y Assembler en una Librería Compartida (.so), que es como una caja de herramientas que Python puede abrir.



1. Modificar el código de C

Crea un archivo nuevo llamado interfaz.c. Es casi igual al anterior, pero sin el main, porque el "dueño" del programa ahora será Python.


```c++
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

```bash
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
```c++

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
```bash
python3 app.py
```


---
resultado:
```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ python3 app.py
[Python] Enviando 42 a la capa C...
[C] Recibi el valor 42 de Python. Llamando a Assembler...
[C] Assembler respondio 43. Devolviendo a Python...
[Python] El resultado final es: 43
```
---

Paso 7: Consumir la API REST en Python

El enunciado te da una URL del Banco Mundial para el índice GINI de Argentina. Si entramos a esa URL, nos devuelve un JSON (un formato de texto que Python entiende como una lista de diccionarios).
Primero, instalá la librería necesaria:

```bash
python3 -m venv env
source env/bin/activate
pip install requests
```

...
modificacion de app.py
```c++
import ctypes
import os
import requests

# 1. Configurar la Librería C (Igual que antes)
lib_path = os.path.abspath("./libcalculo.so")
lib = ctypes.CDLL(lib_path)
lib.procesar_indice.argtypes = (ctypes.c_long,)
lib.procesar_indice.restype = ctypes.c_long

def obtener_gini_argentina():
    # URL oficial del Banco Mundial para Argentina (GINI 2011-2020)
    url = "https://api.worldbank.org/v2/en/country/AR/indicator/SI.POV.GINI?format=json&date=2011:2020"
    
    print(f"[Python] Consultando API del Banco Mundial...")
    response = requests.get(url)
    
    if response.status_code == 200:
        data = response.json()
        # El JSON del Banco Mundial tiene los datos en la posición [1]
        # Buscamos el primer valor que no sea None (el más reciente)
        for registro in data[1]:
            if registro['value'] is not None:
                valor_gini = registro['value']
                anio = registro['date']
                print(f"[Python] Dato encontrado: GINI Argentina ({anio}) = {valor_gini}")
                return valor_gini
    else:
        print("[Python] Error al consultar la API")
        return None

# --- EJECUCIÓN ---
valor_real = obtener_gini_argentina()

if valor_real:
    # OJO: El enunciado dice que Assembler debe convertir de float a entero.
    # Por ahora, como nuestra función C recibe 'long', vamos a redondearlo en Python
    # para probar. Luego lo haremos "legalmente" pasando el float a C.
    valor_entero = int(valor_real) 
    
    print(f"[Python] Enviando {valor_entero} a la capa C...")
    resultado = lib.procesar_indice(valor_entero)
    print(f"[Python] Resultado final (GINI + 1): {resultado}")
```

---
resultados:
```bash
(env) dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ python3 app.py
[Python] Consultando API del Banco Mundial...
[Python] Dato encontrado: GINI Argentina (2020) = 42.7
[Python] Enviando 42 a la capa C...
[C] Recibi el valor 42 de Python. Llamando a Assembler...
[C] Assembler respondio 43. Devolviendo a Python...
[Python] Resultado final (GINI + 1): 43
```
---

PROBLEMAS: sumacomo int no como foat. modiifcacion en calculo.asm:

```asm
section .text
    global sumar_uno

sumar_uno:
    ; El primer argumento float (double) llega en el registro XMM0
    ; Queremos convertirlo a entero y dejarlo en RAX
    
    cvttsd2si rax, xmm0 ; Convierte el double de xmm0 a un entero en rax (ej: 42.7 -> 42)
    add rax, 1          ; Le sumamos 1 (como pide el TP)
    ret
```
---

```c++
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
```

---

recompilar:
```bash
# 1. Assembler (igual que antes)
nasm -f elf64 calculo.asm -o calculo.o

# 2. C (con el flag -fPIC que es necesario para librerías)
gcc -c -fPIC interfaz.c -o interfaz.o

# 3. Unirlos en una librería dinámica (.so)
gcc -shared interfaz.o calculo.o -o libcalculo.so
```
---
```c++
import ctypes
import os
import requests

# 1. Configurar la Librería C (Igual que antes)
lib_path = os.path.abspath("./libcalculo.so")
lib = ctypes.CDLL(lib_path)
lib.procesar_indice.argtypes = (ctypes.c_double,)
lib.procesar_indice.restype = ctypes.c_long

def obtener_gini_argentina():
    # URL oficial del Banco Mundial para Argentina (GINI 2011-2020)
    url = "https://api.worldbank.org/v2/en/country/AR/indicator/SI.POV.GINI?format=json&date=2011:2020"
    
    print(f"[Python] Consultando API del Banco Mundial...")
    response = requests.get(url)
    
    if response.status_code == 200:
        data = response.json()
        # El JSON del Banco Mundial tiene los datos en la posición [1]
        # Buscamos el primer valor que no sea None (el más reciente)
        for registro in data[1]:
            if registro['value'] is not None:
                valor_gini = registro['value']
                anio = registro['date']
                print(f"[Python] Dato encontrado: GINI Argentina ({anio}) = {valor_gini}")
                return valor_gini
    else:
        print("[Python] Error al consultar la API")
        return None

# --- EJECUCIÓN ---
valor_real = obtener_gini_argentina()

if valor_real:

    print(f"[Python] Enviando float {valor_real} a la capa C...")
    resultado = lib.procesar_indice(valor_real)
    print(f"[Python] Resultado final (GINI convertido a int + 1): {resultado}")

```

---
```bash
# Borrar lo anterior para no mezclar
rm *.o *.so

# 1. Assembler
nasm -f elf64 calculo.asm -o calculo.o

# 2. C (interfaz.c)
gcc -c -fPIC interfaz.c -o interfaz.o

# 3. Crear la librería compartida
gcc -shared interfaz.o calculo.o -o libcalculo.so

# ejecutar app:
python3 app.py
```



