⚠️ **DISCLAIMER DE ASISTENCIA CON IA**

Este documento fue mejorado y expandido con asistencia de IA (Claude Haiku). A continuación se detalla qué fue agregado:

### 📝 CAMBIOS Y ADICIONES EN EL README.md

**Contenido original del autor**:
- Pasos de compilación básicos
- Sesión GDB inicial
- Análisis de suma_por_pila
- Información sobre stack y heap

**Contenido agregado por IA** (Estructuración y educativo):
- 🎯 Sección de objetivos del trabajo
- 🏗️ Explicación completa de System V AMD64 ABI con tabla de registros
- 📊 Tabla de registros (Destination Index, Source Index, etc.)
- 🔄 Ciclo de vida detallado de una llamada a función
- 📊 Tabla de desplazamientos en el stack frame with offsets
- 💡 Sección de conceptos clave (Stack Frame, LIFO, Caller-saved vs Callee-saved)
- 🎓 Sección de sugerencias para mejorar la comprensión (ejercicios propuestos)
- ⚠️ Tabla de errores comunes y cómo evitarlos
- 🔍 Sección de investigación profunda
- ✅ Checklist de aprendizaje
- 🏁 Conclusiones educativas
- 📚 Referencias y recursos adicionales

### 📁 ARCHIVOS COMPLEMENTARIOS CREADOS (Fuera del README original)

| Archivo | Propósito |
|---------|-----------|
| **INICIO_RAPIDO.md** | Guía rápida para entender las mejoras realizadas y cómo usarlas |
| **SUGERENCIAS_MEJORA.md** | Ideas basadas en el material teórico para futuras expansiones del README |
| **RESUMEN_MEJORAS.md** | Resumen ejecutivo de cambios, métricas de mejora y valor educativo |
| **GUIA_VISUAL_Y_COMPLEMENTARIA.md** | Recomendaciones para agregar imágenes, Makefile, scripts de testing |
| **ANTES_Y_DESPUES.md** | Comparativas visuales lado-a-lado de 5 ejemplos de mejoras |
| **INDICE_DE_ARCHIVOS.md** | Índice descriptivo de todos los archivos de documentación |
| **00_RESUMEN_FINAL.md** | Resumen final con checklist y próximos pasos |

**Finalidad de estos archivos**: Proveer contexto adicional, sugerencias para mejoras futuras, y demostrar el proceso de transformación de la documentación.

### ✅ NÓ FUE MODIFICADO

- ✅ Los archivos fuente (.c, .s) permanecen intactos
- ✅ El código ejecutable no fue alterado
- ✅ Los análisis técnicos mantienen precisión (basados en el material teórico proporcionado)
- ✅ El trabajo práctico original es completamente tuyo

---

# 🎯 Análisis de Stack Frames y Convenciones de Llamadas en x86-64

**Fuente**: Códigos de ejemplos extraídos de [gitlab.com - stackframe](https://gitlab.com/sistemas-de-computacion-unc/stackframe/-/blob/main/suma.s?ref_type=heads)

---

## 📚 Objetivos del Trabajo

Este trabajo práctico tiene como finalidad:

1. Entender cómo funciona la **convención de llamadas System V AMD64 ABI** en arquitecturas x86-64
2. Comprender el funcionamiento del **stack frame** durante la ejecución de funciones
3. Analizar el rol de los **registros de propósito general** y su relación con los argumentos de funciones
4. Utilizar **GDB** para inspeccionar el estado de la pila, registros y memoria durante la ejecución
5. Estudiar cómo el compilador genera código para pasar argumentos por registro y por pila

---

## 🏗️ Convención de Llamadas: System V AMD64 ABI

En la arquitectura x86-64 bajo Linux, la convención de llamadas **System V AMD64 ABI** establece reglas estrictas sobre:

- **Cómo pasar argumentos** a funciones
- **Dónde devolver resultados**
- **Qué registros preservar** (callee-saved vs caller-saved)
- **Cómo estructurar el stack frame**

### Registros Designados para Argumentos

En System V AMD64 ABI, los primeros **6 argumentos enteros** se pasan mediante registros:

| Registro | Posición | Propósito |
|----------|----------|-----------|
| `%rdi` | 1er argumento | Destination Index |
| `%rsi` | 2do argumento | Source Index |
| `%rdx` | 3er argumento | Data Register |
| `%rcx` | 4to argumento | Counter Register |
| `%r8` | 5to argumento | General Purpose |
| `%r9` | 6to argumento | General Purpose |

**Argumentos adicionales** (7º en adelante) se pasan por la **pila (stack)**.

El **valor de retorno** siempre quedará en `%rax`.

---

## 🔨 Parte I: Función Simple con Dos Argumentos

### Pasos de Compilación y Linkeo Manual

#### 1. Ensamblar el archivo suma.s

```bash
as --64 -g -o suma.o suma.s
```

| Flag | Significado |
|------|-------------|
| `--64` | Modo de 64 bits (x86-64) |
| `-g` | Incluir información de depuración para GDB |

#### 2. Compilar main.c sin linkear

```bash
gcc -g -O0 -c -o main.o main.c
```

| Flag | Significado |
|------|-------------|
| `-g` | Información de depuración |
| `-O0` | **Sin optimizaciones** (fundamental: asegura que los registros sean predecibles) |
| `-c` | Compilar sin linkear |

#### 3. Linkear los objetos

```bash
gcc -o programa main.o suma.o
```

**Nota**: `gcc` resuelve automáticamente las dependencias de `libc` (necesarias para `printf`).

#### 4. Verificar la exportación del símbolo

```bash
nm suma.o | grep suma
```

Debería aparecer: `T suma` (donde `T` indica que el símbolo está en la sección `.text`)

#### 5. Ejecutar el programa

```bash
./programa
```

**Salida esperada**:
```
suma(10, 25) = 35
```
---

## 🐛 Sesión GDB: Depurando la Primera Función

### Iniciando GDB

```bash
gdb ./programa
```

### Establecer Breakpoint

Colocar un breakpoint en la línea donde se llama a `suma()`:

```gdb
(gdb) break main.c:12
```

Alternativamente: `break suma`

### Ejecutar hasta el Breakpoint

```gdb
(gdb) run
```

### Inspeccionar el Assembly Generado

```gdb
(gdb) disassemble main
```

**Salida**:
```asm
Dump of assembler code for function main:
   0x0000555555555139 <+0>:     endbr64
   0x000055555555513d <+4>:     push   %rbp
   0x000055555555513e <+5>:     mov    %rsp,%rbp
   0x0000555555555141 <+8>:     sub    $0x20,%rsp
   0x0000555555555145 <+12>:    movq   $0xa,-0x18(%rbp)      # a = 10
   0x000055555555514d <+20>:    movq   $0x19,-0x10(%rbp)     # b = 25
   0x0000555555555155 <+28>:    mov    -0x10(%rbp),%rdx
   0x0000555555555159 <+32>:    mov    -0x18(%rbp),%rax
   0x000055555555515d <+36>:    mov    %rdx,%rsi             # 2do arg en %rsi
   0x0000555555555160 <+39>:    mov    %rax,%rdi             # 1er arg en %rdi
   0x0000555555555163 <+42>:    call   0x555555555196 <suma> # Llamar a suma
   0x0000555555555168 <+47>:    mov    %rax,-0x8(%rbp)
   ...
End of assembler dump.
```

**Análisis**:
- El compilador carga `a` (10) en `%rdi`
- El compilador carga `b` (25) en `%rsi`
- Luego ejecuta `call suma`, que salta a la función

### Avanzar Instrucción por Instrucción

```gdb
(gdb) stepi
```

Repetir hasta entrar a la función `suma`:

```gdb
(gdb) stepi
suma () at suma.s:13
13  movq    %rdi, %rax   # rax = a (1er argumento)
```

### Examinar los Registros

Verificar el contenido de los registros clave al momento de entrada a `suma`:

```gdb
(gdb) info registers rdi rsi rax
```

**Salida**:
```
rdi            0xa                 10
rsi            0x19                25
rax            0xa                 10
```

**Interpretación**:
- `%rdi` = 10 (primer argumento)
- `%rsi` = 25 (segundo argumento)
- `%rax` = 10 (aún contiene el valor de `%rdi`)

### Ver Todos los Registros

```gdb
(gdb) info registers
```

**Salida parcial**:
```
rax            0xa                 10
rbx            0x7fffffffddd8      140737488346584
rcx            0x555555557dc0      93824992247232
rdx            0x19                25
rsi            0x19                25
rdi            0xa                 10
rbp            0x7fffffffdcb0      0x7fffffffdcb0
rsp            0x7fffffffdc88      0x7fffffffdc88
...
```

### Ejecutar hasta el retorno

```gdb
(gdb) stepi
14  addq    %rsi, %rax   # rax = a + b
(gdb) stepi
15  ret                   # retorna; el resultado está en %rax
```

Verificar el resultado:

```gdb
(gdb) print $rax
$1 = 35
```

### Continuar y Salir

```gdb
(gdb) c
Continuing.
suma(10, 25) = 35
[Inferior 1 (process 45235) exited normally]

(gdb) q
```

---

## 📖 Referencia Rápida de Comandos GDB

| Comando | Descripción |
|---------|-------------|
| `info registers` | Muestra todos los registros |
| `info registers rdi rsi rax` | Muestra registros específicos |
| `print $rax` | Imprime el valor de un registro |
| `x/xg $rsp` | Examina la cima del stack (8 bytes en hex) |
| `disassemble suma` | Muestra el assembly de una función |
| `stepi` (o `si`) | Avanza una instrucción assembler |
| `nexti` (o `ni`) | Avanza sin entrar a funciones |
| `layout regs` | Modo TUI: muestra registros en tiempo real |
| `layout asm` | Modo TUI: muestra assembly en tiempo real |
| `break <línea>` | Establece un breakpoint |
| `run` | Ejecuta el programa |
| `c` | Continúa la ejecución |
| `q` | Sale de GDB |

---

## 🏢 Parte II: Función con 8 Argumentos - Stack Frames Complejos

### Contexto: Pasar Argumentos por Pila

La función `suma_por_pila()` recibe **8 parámetros enteros**:

```c
long suma_por_pila(long r1, long r2, long r3, long r4, long r5, long r6, long a, long b);
```

**Problema**: Como System V AMD64 ABI solo destina 6 registros para parámetros (`%rdi` ... `%r9`), los argumentos 7º y 8º **deben pasar por la pila**.

### Compilación de la Segunda Parte

```bash
as --64 -g -o suma_por_pila.o suma_por_pila.s
as --64 -g -o suma_stack.o suma_stack.s
gcc -o programa2 main2.o suma_por_pila.o suma_stack.o
```

### Depuración con GDB Dashboard

Para una experiencia de depuración más visual, recomendamos usar **GDB Dashboard**:

```bash
gdb ./programa2
```

El dashboard proporciona una interfaz que muestra simultáneamente:
- Registros en tiempo real
- Contenido del stack
- Código assembly
- Historial de comandos

### Inspeccionar el Stack

Para examinar el contenido de la pila desde GDB, utilizamos el comando `x`:

```gdb
(gdb) x/20xw $rsp
```

| Opción | Significado |
|--------|-------------|
| `20` | Cantidad de elementos |
| `x` | Formato hexadecimal |
| `w` | "word" (4 bytes) |
| `$rsp` | Dirección (puntero del stack) |

**Salida de ejemplo**:
```
0x7fffffffdc90:  0x0000000a  0x00000000  0x00000019  0x00000000
0x7fffffffdca0:  0x00000023  0x00000000  0xffffddd8  0x00007fff
0x7fffffffdcb0:  0xffffdd50  0x00007fff  0xf7c2a1ca  0x00007fff
0x7fffffffdcc0:  0xffffdd00  0x00007fff  0xffffddd8  0x00007fff
0x7fffffffdcd0:  0x55554040  0x00000001  0x55555139  0x00005555
```

### Análisis del Stack Frame

Al examinar la memoria en `0x7fffffffdc90`:

- **`0x0000000a`** → Valor **10** (7º argumento: `a`)
- **`0x00000019`** → Valor **25** (8º argumento: `b`)
- **`0x00000023`** → Valor **35** (resultado de suma anterior)
- Resto → Variables locales y datos del stack de `main`

### El Prólogo: Guardando el Stack Frame Anterior

Al entrar a `suma_por_pila`, el código realiza:

```asm
push   %rbp
mov    %rsp,%rbp
```

Esta secuencia cumple dos funciones:

1. **`push %rbp`**: Guarda el registro base anterior en la pila (para poder restaurarlo al salir)
2. **`mov %rsp,%rbp`**: Establece un nuevo punto de referencia (`%rbp`) para acceder a variables locales

### Accediendo a los Argumentos por Pila

Dentro de `suma_por_pila`, para acceder a los argumentos en la pila:

```asm
movq    16(%rbp), %rax   # Cargar 'a' (10) en %rax
addq    24(%rbp), %rax   # Sumar 'b' (25) a %rax
```

**¿Por qué desplazamientos positivos?**

Después de `push %rbp` y `mov %rsp,%rbp`, el stack frame se ve así:

```
-8(%rbp)   ← Variables locales (si hay)
 0(%rbp)   ← %rbp anterior (guardado por push)
 8(%rbp)   ← Dirección de retorno a main
16(%rbp)   ← Argumento 7 (a = 10)
24(%rbp)   ← Argumento 8 (b = 25)
```

Por lo tanto:
- **`16(%rbp)`** apunta al 7º argumento (a)
- **`24(%rbp)`** apunta al 8º argumento (b)

### Visualización Completa del Stack en GDB

Para una visualización de 64 bits (más útil en x86-64):

```gdb
(gdb) x/8xg $rsp
```

**Salida**:
```
0x7fffffffdc88: 0x0000000a0000000a  0x0000000019000000
0x7fffffffdc98: 0x0000002300000000  0x00007ffffffff8
```

Cada línea representa 8 bytes (un "giant word" o `g`).

---

## 🔗 Ciclo de Vida de una Función (Resumen)

### Antes del `call`

1. El compilador coloca los primeros 6 argumentos en registros (`%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8`, `%r9`)
2. Los argumentos restantes se colocan en la pila mediante `push`

### Durante el `call`

1. La instrucción `call suma_por_pila` apila la **dirección de retorno** de forma automática
2. El control salta a la función

### En el Prólogo de la Función

1. `push %rbp` → Guarda el %rbp anterior
2. `mov %rsp,%rbp` → Crea un nuevo stack frame

### Durante la Ejecución

- Variables locales se crean con `sub $X, %rsp`
- Acceso a argumentos: `N(%rbp)` donde N = 8 + (4 × número_de_argumento_stack)
- Acceso a variables locales: `-M(%rbp)` donde M es el desplazamiento negativo

### En el Epílogo

1. `mov %rbp,%rsp` → Restaura el puntero del stack
2. `pop %rbp` → Restaura el %rbp anterior
3. `ret` → Retorna a la dirección guardada en la pila

---

## 📊 Tabla de Desplazamientos en el Stack Frame

| Ubicación | Contenido | Acceso |
|-----------|-----------|--------|
| -24(%rbp) | Variable local 3 | `mov -24(%rbp), %rax` |
| -16(%rbp) | Variable local 2 | `mov -16(%rbp), %rax` |
| -8(%rbp) | Variable local 1 | `mov -8(%rbp), %rax` |
| **0(%rbp)** | **%rbp anterior** | **Guardado por push %rbp** |
| **8(%rbp)** | **Dirección de retorno** | **Guardada automáticamente por call** |
| 16(%rbp) | Argumento 7 | `mov 16(%rbp), %rax` |
| 24(%rbp) | Argumento 8 | `mov 24(%rbp), %rax` |

---

## 💡 Conceptos Clave Aprendidos

### 1. **Stack Frame (Marco de Pila)**

Es la región de memoria asignada para cada invocación de función. Contiene:
- Variables locales
- Dirección de retorno
- Estado de registros guardados
- Argumentos pasados por pila

### 2. **LIFO (Last In, First Out)**

La pila funciona como el principio de última entrada, primera salida:
- Último dato apilado es el primero en desapilarse
- La memoria se expande hacia direcciones **menores** en x86-64

### 3. **Registros Caller-Saved vs Callee-Saved**

- **Caller-saved** (`%rax`, `%rcx`, `%rdx`): El llamador debe guardarlos si los necesita después
- **Callee-saved** (`%rbp`, `%rsp`): La función llamada debe preservarlos

### 4. **Importancia de `-O0`**

La flag `-O0` (sin optimizaciones) es crítica para depuración porque:
- El compilador **no optimiza** el código
- Los registros contienen valores **predecibles**
- El flujo del código es **fácil de seguir**

Con optimizaciones mayores, el compilador puede:
- Eliminar variables locales
- Reutilizar registros
- Cambiar el orden de instrucciones
- Hacer el debug **mucho más difícil**

---

## 🎓 Sugerencias para Mejorar la Comprensión

### Ejercicios Propuestos

1. **Modificar el número de argumentos**: 
   - Crea una función con 10 argumentos y observa cómo se asignan 4 más en la pila
   - Usa GDB para inspeccionar los desplazamientos

2. **Comparar optimizaciones**:
   - Compila el mismo código con `-O0`, `-O1`, `-O2`, `-O3`
   - Ejecuta `disassemble main` en cada caso
   - Observa cómo cambia el código generado

3. **Debuggear variables locales**:
   - Agrega variables locales a `suma_por_pila`
   - Usa GDB para inspeccionar sus ubicaciones en el stack
   - Verifica los desplazamientos negativos

4. **Inspeccionar registros durante ejecución**:
   - Usa `layout regs` en GDB para ver registros en tiempo real
   - Ejecuta `si` (step into) instrucción por instrucción
   - Observa cómo cambian los valores en vivo

### Herramientas Recomendadas

- **GDB Dashboard**: Interfaz visual mejorada para GDB
- **Radare2** (`r2`): Análisis de binarios avanzado
- **Ghidra**: Descompilación interactivo (por NSA)
- **objdump**: Ver información de objetos compilados

```bash
# Ver secciones y símbolos
objdump -d programa | grep -A 20 "main>:"

# Ver información de headers
objdump -h programa
```

---

## 📝 Errores Comunes y Cómo Evitarlos

| Error | Causa | Solución |
|-------|-------|----------|
| **Registros con valores inesperados** | Compilador optimizando | Usar `-O0` |
| **Segmentation Fault** | Stack overflow o corrupción | Inspeccionar `%rsp` y `%rbp` |
| **Variables no visibles en GDB** | Optimizaciones del compilador | Compilar con `-g3` |
| **Argumentos no en registros esperados** | ABI diferente o arquitectura | Verificar `uname -m` (debe ser x86_64) |
| **No poder setear breakpoints** | Falta de símbolos de debug | Compilar con `-g` |

---

## 🔍 Investigación Profunda: System V AMD64 ABI

Para quienes deseen entender más a fondo la convención de llamadas:

### Documentación Oficial

La especificación completa está disponible en:
- **PDF**: AMD64 ABI (System V AMD64 ABI)
- **HTML**: https://gitlab.com/sistemas-de-computacion-unc/stackframe

### Puntos Clave del ABI

1. **Parámetros de Punto Flotante**: Se pasan en registros XMM (`%xmm0`-`%xmm7`)
2. **Variadic Functions**: Requieren `%al` con el número de argumentos XMM
3. **Red Zone**: Zone debajo de `%rsp` que no es modificada por interrupciones
4. **Stack Alignment**: El stack debe estar alineado a 16 bytes en cada `call`

---

## 📚 Recursos Adicionales

### Libros Recomendados

- **"Computer Systems: A Programmer's Perspective"** (CS:APP)
  - Capítulos sobre Assembly y Stack
  - Ejercicios prácticos excelentes

- **"Lenguaje Ensamblador para PC"** (Paul A. Carter)
  - Enfoque desde lo básico hasta avanzado
  - Disponible en español

### Tutoriales en Línea

- **eli.thegreenplace.net**: Túnel profundo en stack frames
  - https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64

- **OSDev.org**: Desarrollo de sistemas operativos
  - Sección de calling conventions

### Comandos GDB Útiles Avanzados

```gdb
# Mostrar información de la función actual
(gdb) info frame

# Mostrar toda la pila de llamadas
(gdb) backtrace full

# Examinar 16 words desde %rsp
(gdb) x/16xw $rsp

# Examinar string en memoria
(gdb) x/s 0x555555556004

# Watchpoint: parar si una dirección cambia
(gdb) watch *(int*) 0x7fffffffdc90

# Display automático en cada paso
(gdb) display $rax
(gdb) display $rsp
```

---

## ✅ Checklist de Aprendizaje

Antes de dar por completado este TP, verifica que comprendiste:

- [ ] Cómo se cargan argumentos en registros vs en pila
- [ ] La estructura de un stack frame
- [ ] Cómo se accede a argumentos dentro de una función
- [ ] El rol de `%rbp` como punto de referencia
- [ ] Por qué se guardan registros al inicio de una función
- [ ] La diferencia entre desplazamientos positivos y negativos desde `%rbp`
- [ ] Cómo GDB te permite inspeccionar memoria en vivo
- [ ] El impacto de las optimizaciones del compilador en el debug

---

## 🏁 Conclusiones

Este trabajo demostró la **importancia de entender la arquitectura de bajo nivel**:

1. **El compilador no es mágico**: Genera código determinista siguiendo reglas precisas (ABI)
2. **El stack es el corazón**: Gran parte de la ejecución depende de este mecanismo
3. **GDB es tu aliado**: Inspeccionar en vivo es la mejor forma de aprender
4. **Los detalles importan**: Un desplazamiento incorrecto puede causar bugs sutiles

La comprensión profunda de convenciones de llamadas es esencial para:
- **Debugging efectivo** de errores complejos
- **Optimización** de código crítico
- **Seguridad**: Protección contra exploits basados en stack overflow
- **Interoperabilidad**: Llamar código en diferentes lenguajes

---

## 📞 Referencias

1. **Documentación oficial del proyecto**:
   - https://gitlab.com/sistemas-de-computacion-unc/stackframe/

2. **Wikipedia - x86-64**:
   - https://en.wikipedia.org/wiki/X86-64

3. **GDB Documentation**:
   - https://sourceware.org/gdb/documentation/

4. **AMD64 ABI Specification**:
   - System V AMD64 ABI (proceedocumentation)




