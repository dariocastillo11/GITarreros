# TP2: API - Integración Ensamblador, C y Python

## Descripción General

En este trabajo se utilizarán programas en lenguaje ensamblador, C y Python que luego serán conectados entre sí por medio de API. Por este motivo necesitamos utilizar **NASM**, un assembler y disassembler para la arquitectura x86, que traduce lenguaje ensamblador en código ejecutable para máquina.

## Instalación de Dependencias

Primero, instala NASM y las dependencias necesarias:

```bash
sudo apt install build-essential nasm gcc-multilib g++-multilib libcurl4-openssl-dev
```
## Paso 1: Crear el Código Assembler

En este caso utilizaremos el siguiente código para sumar 1 a un registro:

```asm
sumar_uno:
        ; Por convención (System V ABI):
        ; El primer argumento que manda C llega en el registro RDI
        ; El resultado que devolvemos a C debe quedar en el registro RAX
        
        mov rax, rdi    ; Pasamos el número recibido a RAX
        add rax, 1      ; Le sumamos 1
        ret             ; Volvemos a C
```

### Compilar el Assembler

Compila el código Assembler con el siguiente comando:

```bash
nasm -f elf64 sumar.asm -o sumar.o
```

Este comando genera un archivo `.o`, que es un paso intermedio entre lenguaje legible por personas y un programa ejecutable. Se genera un archivo de código binario que puede ser ejecutado por la máquina.

## Paso 2: Crear el Código C

Este archivo será utilizado dentro de un programa escrito en C. En nuestro caso, el código utilizado será:

```c
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
```

### Compilar el Programa C

Para compilar el programa en C y vincularlo con el de ASM, utiliza los siguientes comandos:

```bash
gcc -c main.c -o main.o
gcc main.o sumar.o -o mi_programa
```

Esto genera un archivo ejecutable que mostrará el funcionamiento buscado:

```bash
./mi_programa
```

## Paso 3: Crear una Librería Compartida para Python

Para este trabajo, se busca utilizar el programa previamente armado y conectarlo con Python. Esto se logra convirtiéndolo en una librería compartida `.so` para que Python pueda utilizarla.

### Generar la Librería

Utiliza los siguientes comandos para generar la librería:

```bash
gcc -c -fPIC interfaz.c -o interfaz.o
gcc -shared interfaz.o sumar.o -o libsumar.so
```

### Usar la Librería en Python

La librería será referenciada dentro del siguiente programa en Python utilizando `ctypes`:

```python
import ctypes
import os

# 1. Cargar la librería que acabamos de crear
lib_path = os.path.abspath("./libsumar.so")
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

### Ejecutar el Programa

Para probar el funcionamiento de la conexión entre estos lenguajes, ejecuta:

```bash
uv run app.py
```

**Nota sobre `uv`**: Se utiliza `uv`, que es un gestor de ambiente virtual para Python, encargado de manejar y descargar de manera local en el proyecto las dependencias que necesite nuestro programa. Esto evita problemas de sincronización con distintas versiones de dependencias en proyectos previos o posteriores.

### Salida Esperada

El resultado es el siguiente:

```
[Python] Enviando 42 a la capa C...
[C] Recibi el float 0.000000 de Python. Llamando a Assembler...
[C] Assembler respondio 1. Devolviendo a Python...
[Python] El resultado final es: 1
```

## Paso 4: Extración de Datos GINI de la API del Banco Mundial

A continuación, se realiza un programa que extrae el índice GINI de la API del Banco Mundial (en este caso, el índice correspondiente a Argentina) y le suma +1 aplicando los medios utilizados previamente.

Al extraer estos datos, obtenemos un archivo JSON que será leído mediante Python.

### Código Python para Consultar la API

```python
import ctypes
import os
import requests

# 1. Configurar la Librería C (Igual que antes)
lib_path = os.path.abspath("./libsumar.so")
lib = ctypes.CDLL(lib_path)
lib.procesar_indice.argtypes = (ctypes.c_double,)
lib.procesar_indice.restype = ctypes.c_double

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
    #valor=int(valor_real)
    print(f"[Python] Enviando float {valor_real} a la capa C...")
    resultado = lib.procesar_indice(valor_real)
    print(f"[Python] Resultado final (GINI convertido a int + 1): {resultado}")
```

### Salida Esperada

```
[Python] Consultando API del Banco Mundial...
[Python] Dato encontrado: GINI Argentina (2020) = 42.7
[Python] Enviando float 42.7 a la capa C...
[C] Recibi el float 42.700000 de Python. Llamando a Assembler...
[C] Assembler respondio 43.000000. Devolviendo a Python...
[Python] Resultado final (GINI convertido a int + 1): 43.0
```


