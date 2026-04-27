# 📋 Sugerencias de Mejora para el README.md

## Basado en el Material Teórico Proporcionado

---

## 1️⃣ **Secciones que DEBERÍAS AGREGAR**

### A. Explicación Visual del Stack Frame (MUY IMPORTANTE)

Basándote en el documento teórico, agrega un diagrama ASCII como este:

```markdown
### Visualización del Stack Frame detallada

Después de ejecutar `push %rbp` y `mov %rsp,%rbp` en suma_por_pila:

```
    ┌─────────────────────────────────┐
    │  STACK DE MAIN (más abajo)       │
    ├─────────────────────────────────┤
... │   Variable b = 25 (0x19)        │  ← 0x7fffffffd1b8
    ├─────────────────────────────────┤
... │   Variable a = 10 (0x0a)        │  ← 0x7fffffffd1b0
    ├─────────────────────────────────┤
... │   Variable resultado = 35       │  ← 0x7fffffffd1c0
    └─────────────────────────────────┘
    
    ┌─────────────────────────────────┐
[Argumentos por Stack]
    ├─────────────────────────────────┤
    │   8vo arg: b = 25 (0x19)        │  ← 0x7fffffffd1a8 = 24(%rbp)
    ├─────────────────────────────────┤
    │   7mo arg: a = 10 (0x0a)        │  ← 0x7fffffffd1a0 = 16(%rbp)
    ├─────────────────────────────────┤
[Dirección de Retorno]
    │   RIP a main+127 (0x555551b8)   │  ← 0x7fffffffd198 = 8(%rbp)
    ├─────────────────────────────────┤
[Stack Frame Local]
    │   %rbp anterior (main)          │  ← 0x7fffffffd190 = 0(%rbp)
    └─────────────────────────────────┘
    %rbp apunta aquí →
```

**Información que es importante destacar**:
- El viejo %rbp queda en 0(%rbp)
- La dirección de retorno en 8(%rbp)
- Los argumentos extra en 16(%rbp) y 24(%rbp)
- Los desplazamientos son SIEMPRE positivos desde %rbp en el prólogo
```

### B. Comparativa: Argumentos por Registros vs Por Pila

```markdown
### Argumento 1-6: En Registros (System V AMD64 ABI)

| Argumento | Registro | Ejemplo |
|-----------|----------|---------|
| 1º | %rdi | primer parámetro |
| 2º | %rsi | segundo parámetro |
| 3º | %rdx | tercer parámetro |
| 4º | %rcx | cuarto parámetro |
| 5º | %r8 | quinto parámetro |
| 6º | %r9 | sexto parámetro |

**VENTAJA**: Más rápido (no requiere acceso a memoria)

### Argumento 7+: En la Pila

Se apilan en orden inverso (el 8º primero, el 7º después):

```bash
push $0x19  # Argumento 8 (b=25) se apila primero
push $0xa   # Argumento 7 (a=10) se apila después
call suma_por_pila
```

**VENTAJA**: Permite función con número variable de argumentos
```

### C. Análisis Detallado del Prólogo y Epílogo

```markdown
### Prólogo de Función (Busca en suma_por_pila.s)

```asm
suma_por_pila+0:
    push   %rbp           # Guarda el %rbp anterior
    mov    %rsp,%rbp      # Establece nuevo stack frame
    sub    $0x10,%rsp     # Asigna espacio para vars locales (si hay)
```

**Qué hace**:
1. Preserva el estado anterior (para poder restaurar)
2. Crea un "anclaje" del nuevo frame
3. Asigna memoria LOCAL si necesita variables

### Epílogo de Función

```asm
suma_por_pila+8:
    mov    %rbp,%rsp      # Restaura el puntero anterior
    pop    %rbp           # Recupera %rbp anterior
    ret                   # Salta a dirección de retorno
```

**Qué hace**:
1. Deshace los cambios del prólogo
2. Retorna el control a main
```

### D. Rol de Cada Registro - Tabla Extendida

```markdown
### Registros de Propósito General en x86-64

| Registro | 64-bit | 32-bit | Rol Principal | Preservado |
|----------|--------|--------|---------------|-----------|
| rax/eax | %rax | %eax | **Valor de retorno** | ❌ |
| rbx/ebx | %rbx | %ebx | Uso general | ✅ |
| rcx/ecx | %rcx | %ecx | **4to argumento**, contador de loops | ❌ |
| rdx/edx | %rdx | %edx | **3er argumento**, datos extra | ❌ |
| rsi/esi | %rsi | %esi | **2do argumento** | ❌ |
| rdi/edi | %rdi | %edi | **1er argumento** | ❌ |
| rsp | %rsp | n/a | **Stack pointer** | ✅ |
| rbp | %rbp | n/a | **Base pointer** | ✅ |
| r8-r11 | | | 5to-8vo args | ❌ |
| r12-r15 | | | Propósito general | ✅ |

✅ = Callee-saved (función debe preservarlo)
❌ = Caller-saved (función puede modificarlo)
```

---

## 2️⃣ **Información que FALTA Según el Documento Teórico**

### A. Explicar `Little Endian`

En el documento teórico se menciona esto pero NO en tu README:

```markdown
### Nota Importante: Little Endian en x86-64

Cuando ves en el stack:

```
0x7fffffffd198: 0x555551b8 0x00005555
```

En realidad, la dirección completa es: **0x00005555555551b8**

Esto es porque x86-64 usa **Little Endian**: 
- Byte menos significativo primero
- La dirección se lee de **derecha a izquierda**

Por eso ves dos valores de 32 bits que forman un valor de 64 bits.

**Con `x/xg` (giant words)** ves de una vez los 8 bytes:
```
0x7fffffffd198: 0x00005555555551b8
```
```

### B. Explicar la Instrucción `leave`

```markdown
### La Instrucción `leave` (Atajo útil)

Algunos compiladores generan:

```asm
leave    # Equivale a: mov %rbp,%rsp / pop %rbp
```

Es un atajo de dos instrucciones en una:
1. Restaura %rsp desde %rbp
2. Restaura %rbp desde la pila

Aunque algunas fuentes modernas lo evitan por razones de performance.
```

### C. Cómo Manualmente Hacer Push en Inline Assembly

Basado en main2.c que proporcionaste:

```markdown
### Pasar Argumentos Manualmente por Pila (main2.c)

En main2.c, Facundo pasa argumentos manualmente:

```c
__asm__ (
    "pushq %[b]\n\t"        // Apila 'b' (2do arg)
    "pushq %[a]\n\t"        // Apila 'a' (1er arg)
    "call suma_stack\n\t"   // Llama a la función
    "addq $16, %%rsp\n\t"   // Limpia 2 argumentos (2×8 bytes)
    : "=a" (resultado)      // Output: resultado en %rax
    : [a] "r" (a), [b] "r" (b)  // Input: a y b en registros
    : "memory"              // Clobber list
);
```

**Análisis**:
- Manual push de argumentos (emulando cdecl)
- Limpieza del stack: suma 16 bytes (2 args × 8 bytes)
- El resultado se lee desde %rax mediante `"=a"` constraint
```

---

## 3️⃣ **Secciones que DEBERÍAS EXPANDIR**

### A. Ejemplos de Debugging Paso a Paso

Agrega exactamente lo que hiciste en GDB:

```markdown
### Sesión Completa: Paso a Paso hacia suma()

```bash
$ gdb ./programa
(gdb) break main.c:12
Breakpoint 1 at 0x555555555148
(gdb) run
Starting program: /path/to/programa 

Breakpoint 1, main () at main.c:12

(gdb) disassemble main
... [output assembly] ...

(gdb) stepi            # Paso 1: mov -0x10(%rbp),%rdx
(gdb) x/3i $rip        # Ver próximas 3 instrucciones
(gdb) info registers rdi rsi rdx  # Ver estado

rdi    0xa     10
rsi    0x0     0
rdx    0x19    25

(gdb) stepi            # Paso 2: mov -0x18(%rbp),%rax
(gdb) info registers rdi rsi rax

rdi    0xa     10
rsi    0x0     0
rax    0xa     10

(gdb) stepi            # Paso 3: mov %rdx,%rsi
(gdb) info registers rsi
rsi    0x19    25

(gdb) stepi            # Paso 4: mov %rax,%rdi  
(gdb) info registers rdi rsi

rdi    0xa     10  ← Primer argumento listo
rsi    0x19    25  ← Segundo argumento listo

(gdb) stepi            # Paso 5: call suma
... ahora estamos dentro de suma() ...

(gdb) info registers rdi rsi rax
rdi    0xa     10  ← La función LO VE AQUÍ
rsi    0x19    25  ← La función LO VE AQUÍ
rax    0xa     10
```

**Conclusión**: El compilador prepara argumentos en registros antes del `call`
```

### B. Comparación: -O0 vs -O2

```markdown
### Impacto de Optimizaciones en el Assembly

[Agrega aquí el output de]

```bash
gcc -O0 -c main.c       # Tu actual
gcc -O2 -c main.o       # Versión optimizada
objdump -d main.o       # Compara el output
```

Mostrarás cómo el compilador:
- Elimina variables innecesarias
- Reordena instrucciones
- Usa registros más eficientemente
- Hace el debugging imposible
```

---

## 4️⃣ **Gráficos y Diagramas que DEBERÍAS AGREGAR**

### A. Flujo de Control durante una Llamada a Función

```txt
┌─────────────────────────────┐
│  main()                     │
│  ...                        │
│  mov %rax, %rdi  (arg 1)   │
│  mov %rdx, %rsi  (arg 2)   │
│  call suma ──────┐          │
│  (siguiente)     │          │
└──────────────────┼──────────┘
                   │
                   ↓
        ┌──────────────────────┐
        │  suma()              │
        │  mov %rdi, %rax      │
        │  add %rsi, %rax      │
        │  ret ────────┐       │
        └─────────────┼────────┘
                      │
                      ↓
        ┌─ Los registros se restauran
        │  El resultado está en %rax
        │
        (vuelve a main)
```

### B. Estructura del Stack Frame completo (antes, durante, después)

Ve el documento PDF - tienes imágenes exactas que deberías replicar en ASCII o describirlas mejor.

---

## 5️⃣ **Cosas que DEBERÍAS VERIFICAR**

Antes de dar el trabajo final:

- [ ] ¿El README.md tiene links a las imágenes correctos?
- [ ] ¿Los comandos de GDB están testeados y funcionan?
- [ ] ¿Las direcciones de memoria coinciden con el output real?
- [ ] ¿Explicas POR QUÉ cada desplazamiento (16, 24, etc.)?
- [ ] ¿Hay un diagrama visual del stack completo?
- [ ] ¿Mencionas qué es cdecl vs System V?
- [ ] ¿Incluyes los archivos .s (suma.s, suma_por_pila.s)?
- [ ] ¿Mencionas por qué %rsp y %rbp son especiales?

---

## 6️⃣ **Información Adicional Basada en el PDF**

El documento teórico menciona:

### "Red Zone" (No lo mencionas)

```markdown
### La Red Zone en x86-64

En System V AMD64 ABI, existe una región especial de 128 bytes:
- Ubicación: 128 bytes **debajo** de %rsp
- Uso: Datos temporales que no son modificados por interrupciones
- Ventaja: Skip de `sub $128, %rsp` si solo necesitas espacio temporal

Muy pocas personas lo usan, pero es importante conocer.
```

### Convención CDECL (Lo mencionas pero no lo explicas bien)

```markdown
### CDECL vs System V AMD64 ABI

**CDECL** (antigua convención de 32 bits):
- Argumentos en pila (push de derecha a izquierda)
- El caller limpia la pila (`add $X, %esp`)
- Más lento, menos eficiente

**System V AMD64 ABI** (moderna, 64 bits):
- Primeros 6 argumentos en registros
- Argumentos extra en pila
- El caller TAMBIÉN limpia la pila (`add $X, %rsp`)
- Más rápido, mejor uso de registros

Tu función `suma_por_pila` usa **System V AMD64**, no cdecl.
```

---

## 7️⃣ **Estructura Mejorada para tu README**

Sugiero este orden:

1. **Introducción** ✅ (ya hicimos esto)
2. **Conceptos Teóricos**
   - System V AMD64 ABI
   - Stack Frames
   - Registros (agregar más detalle)
3. **Parte I: Simple** ✅ (ya está)
4. **Parte II: Con Stack**
   - Explicación del prólogo/epílogo
   - Análisis detallado del stack
   - Diagramas ASCII
5. **Debugging Avanzado**
   - Comandos GDB útiles
   - Casos de uso prácticos
6. **Conclusiones** ✅ (agregamos esto)
7. **Referencias** ✅ (agregamos esto)

---

## 🎯 **Resumen de Cambios Aplicados a tu README.md**

✅ Agregamos estructura clara con títulos
✅ Mejor formato de código
✅ Tablas para información
✅ Explicaciones más detalladas
✅ Comandos GDB mejorados
✅ Sección de conceptos clave
✅ Checklist de aprendizaje
✅ Sugerencias de ejercicios

**TODAVÍA PUEDES AGREGAR**:
- Diagramas ASCII más detallados del stack
- Explicación de Little Endian
- Comparación -O0 vs -O2
- Ejemplos de gdp Dashboard
- Links a las imágenes (si las tienes)
- Variables locales en el stack frame

---

## 💡 Última Sugerencia

Cuando termines de incorporar todo esto, agrega una **sección de "Ejecución Práctica"**:

```markdown
### Ejecución Práctica

1. Clona/descarga todos los archivos (.c, .s)
2. Ejecuta: `make` (si tienes Makefile) o los comandos de compilación
3. Ejecuta: `./programa` y `./programa2`
4. Ejecuta: `gdb ./programa` y sigue los pasos indicados
5. Experimenta modificando los valores de `a` y `b`
6. Observa cómo cambian los registros en GDB
```

Esto hace que tu README sea **ejecutable** y **reproducible**.

---

**¡Éxito con el trabajo! Este README.md mejorado será de gran valor tanto para ti como para tu profesor.**
