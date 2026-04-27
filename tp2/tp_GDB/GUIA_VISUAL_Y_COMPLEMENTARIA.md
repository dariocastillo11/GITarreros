# 📸 Recomendaciones de Contenido Visual y Complementario

## Para Completar tu TP tp_GDB

---

## 1️⃣ **IMÁGENES que DEBERÍAS TOMAR/INCLUIR**

### A. Screenshots de GDB Dashboard

**Qué capturar:**
1. Vista completa cuando pausas en `suma()`
   - Registros en vivo
   - Stack en vivo
   - Assembly en vivo
   - Variables

2. Stacktrace completo (`backtrace`)

3. Output de `x/20xw $rsp` antes, durante, después

**Dónde incluirlas:**
```markdown
### Depuración con GDB Dashboard

![Registros en la entrada a suma](./img/gdb-dashboard-part1.png)

**Observa:**
- %rdi = 0xa (10)
- %rsi = 0x19 (25)
- %rax = 0xa

![Stack después del prólogo](./img/gdb-dashboard-part2.png)
```

### B. Comparativa Visual: Antes y Después

| Elemento | Antes | Después |
|----------|-------|---------|
| Imagen | [captura -O0] | [captura -O2] |
| Assembly | Predecible | Optimizado |
| Disassemble | Claro | Difícil |
| Debug | Fácil | Imposible |

### C. Diagrama del Stack Completo

```
Tomar un screenshot de GDB mostrando:
- x/30xg $rsp (30 palavras de 8 bytes)
- Marcar con anotaciones:
  - Dónde está %rbp
  - Dónde está la dirección de retorno
  - Dónde están los argumentos
  - Dónde están variables locales
```

---

## 2️⃣ **FORMATO MARKDOWN AVANZADO**

### Colapsables (para no saturar)

Puedes usar HTML en Markdown:

```markdown
<details>
<summary>📝 Click para ver output completo de GDB</summary>

(gdb) info registers
rax    0xa         10
rbx    0x7fff...   ...
... (mucho más)

</details>
```

### Bloques de Nota/Advertencia

```markdown
> 💡 **Tip**: Siempre compila con -g para GDB

> ⚠️ **Advertencia**: Sin -O0, los registros pueden engañar

> ❌ **Error Común**: Olvidar limpiar el stack después del call
```

---

## 3️⃣ **ARCHIVOS COMPLEMENTARIOS que PUEDES AGREGAR**

### A. Makefile para Facilitar Compilación

```makefile
# tp2/tp_GDB/Makefile

CC = gcc
AS = as
CFLAGS = -g -O0
ASFLAGS = --64 -g

# Targets para Parte I
programa: main.o suma.o
	$(CC) -o programa main.o suma.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

suma.o: suma.s
	$(AS) $(ASFLAGS) -o suma.o suma.s

# Targets para Parte II
programa2: main2.o suma_por_pila.o suma_stack.o
	$(CC) -o programa2 main2.o suma_por_pila.o suma_stack.o

main2.o: main2.c
	$(CC) $(CFLAGS) -c main2.c

suma_por_pila.o: suma_por_pila.s
	$(AS) $(ASFLAGS) -o suma_por_pila.o suma_por_pila.s

suma_stack.o: suma_stack.s
	$(AS) $(ASFLAGS) -o suma_stack.o suma_stack.s

# Utilidades
debug: programa
	gdb ./programa

debug2: programa2
	gdb ./programa2

clean:
	rm -f *.o programa programa2

.PHONY: debug debug2 clean
```

**Uso:**
```bash
make              # Compila todo
make programa     # Solo programa 1
make debug        # Abre GDB automáticamente
make clean        # Limpia compilación
```

### B. Script para Automatizar Debugging

```bash
#!/bin/bash
# gdb-debug.sh

echo "╔════════════════════════════════════════╗"
echo "║     GDB Automated Debugging Script     ║"
echo "╚════════════════════════════════════════╝"

# Compilar
echo "[*] Compilando..."
make clean > /dev/null 2>&1
make programa

if [ ! -f ./programa ]; then
    echo "[ERROR] Compilación fallida"
    exit 1
fi

# GDB Commands
cat > /tmp/gdb_commands.txt <<EOF
break main.c:12
run
disassemble main
stepi
stepi
stepi
stepi
stepi
info registers rdi rsi rax
x/8xg \$rsp
continue
EOF

echo "[*] Iniciando GDB con breakpoint automático..."
gdb -x /tmp/gdb_commands.txt ./programa

# Cleanup
rm /tmp/gdb_commands.txt
```

**Uso:**
```bash
chmod +x gdb-debug.sh
./gdb-debug.sh
```

### C. Archivo de Referencia Rápida

```markdown
# QUICK_REFERENCE.md

## Compilación Rápida

### Una línea para compilar todo (Parte I)
\`\`\`bash
as --64 -g -o suma.o suma.s && gcc -g -O0 -c main.c && gcc -o programa main.o suma.o && ./programa
\`\`\`

### Una línea para compilar todo (Parte II)
\`\`\`bash
as --64 -g -o suma_por_pila.o suma_por_pila.s && as --64 -g -o suma_stack.o suma_stack.s && gcc -g -O0 -c main2.c && gcc -o programa2 main2.o suma_por_pila.o suma_stack.o && ./programa2
\`\`\`

## Comandos GDB Más Usados

| Comando | Descripción |
|---------|-------------|
| `b main.c:12` | Breakpoint en línea 12 |
| `r` | Run |
| `si` | Step into (assembly) |
| `ni` | Next instruction |
| `info registers` | Ver todos los registros |
| `print $rax` | Ver valor de %rax |
| `x/8xg $rsp` | Ver stack |
| `disassemble main` | Ver assembly |
| `c` | Continue |
| `q` | Quit |
```

---

## 4️⃣ **ESTRUCTURA SUGERIDA PARA CARPETAS**

```
tp2/tp_GDB/
├── README.md                    (✅ Ya mejorado)
├── SUGERENCIAS_MEJORA.md       (✅ Agregado)
├── RESUMEN_MEJORAS.md          (✅ Agregado)
├── QUICK_REFERENCE.md          (Recomendado agregar)
├── Makefile                    (Recomendado agregar)
├── gdb-debug.sh               (Recomendado agregar)
│
├── src/
│   ├── main.c
│   ├── main2.c
│   ├── suma.s
│   ├── suma_por_pila.s
│   └── suma_stack.s
│
├── img/                        (Si incluyes screenshots)
│   ├── gdb-dashboard-1.png
│   ├── gdb-dashboard-2.png
│   ├── stack-frame-diagram.png
│   └── registros-ejemplo.png
│
└── docs/
    ├── debugging-guide.md
    ├── abi-explained.md
    └── gdb-commands.md
```

---

## 5️⃣ **TESTS/VALIDACIÓN que PUEDES AGREGAR**

### Test Script

```bash
#!/bin/bash
# test.sh

echo "═════════════════════════════════════"
echo "Testing suma functions"
echo "═════════════════════════════════════"

# Compile
make clean > /dev/null && make > /dev/null

# Test Case 1
echo "Test 1: suma(10, 25)"
OUTPUT=$(./programa)
if [[ $OUTPUT == *"35"* ]]; then
    echo "✅ PASS"
else
    echo "❌ FAIL"
fi

# Test Case 2: suma_por_pila
echo "Test 2: suma_por_pila(0,0,0,0,0,0,10,25)"
OUTPUT=$(./programa2)
if [[ $OUTPUT == *"35"* ]]; then
    echo "✅ PASS"
else
    echo "❌ FAIL"
fi

echo "═════════════════════════════════════"
```

---

## 6️⃣ **INFORMACIÓN EXTRA EN COMENTARIOS**

### Para Stack Frame

Agrega comentarios detallados en suma_por_pila.s:

```asm
; ============================================================
; suma_por_pila: Suma dos números pasados por pila
; 
; Argumentos en registros (System V AMD64 ABI):
;   %rdi ... %r9 = argumentos 1-6
;
; Argumentos en pila:
;   16(%rbp) = 7mo argumento (primero pasado en pila)
;   24(%rbp) = 8vo argumento
;
; Retorna en %rax
; ============================================================

suma_por_pila:
    ; PRÓLOGO
    push %rbp               ; Guardar %rbp anterior
    mov %rsp,%rbp          ; Establecer nuevo frame
    
    ; Ahora el stack se ve así:
    ;   0(%rbp)   <- %rbp anterior (recién guardado)
    ;   8(%rbp)   <- Dirección de retorno (guardada por call)
    ;  16(%rbp)   <- Argumento 7 (a = 10)
    ;  24(%rbp)   <- Argumento 8 (b = 25)
    
    ; CUERPO
    mov 16(%rbp), %rax      ; %rax = argumento 7
    add 24(%rbp), %rax      ; %rax += argumento 8
    
    ; EPÍLOGO
    pop %rbp                ; Restaurar %rbp
    ret                     ; Volver a main
```

---

## 7️⃣ **COMPARATIVAS QUE PUEDES MOSTRAR**

### Antes/Después de Optimización

```markdown
## Comparativa: -O0 vs -O2

### Compilación sin optimizar
\`\`\`bash
gcc -O0 -g -c main.c -o main.o
\`\`\`

Output de disassemble (claro, predecible):
\`\`\`asm
mov   $0xa,-0x18(%rbp)      # a = 10
mov   $0x19,-0x10(%rbp)     # b = 25
mov   -0x10(%rbp),%rdx      # rdx = b
mov   -0x18(%rbp),%rax      # rax = a
mov   %rdx,%rsi             # rsi = b
mov   %rax,%rdi             # rdi = a
call  suma
\`\`\`

### Compilación con optimizar
\`\`\`bash
gcc -O2 -g -c main.c -o main.o
\`\`\`

Output de disassemble (comprimido, difícil de leer):
\`\`\`asm
mov    $0x19,%esi
mov    $0xa,%edi
call   suma
\`\`\`

**Diferencias:** O2 elimina variables innecesarias y pasa directamente en registros
```

---

## 8️⃣ **NARRACIÓN PASO A PASO**

Crea una "novela" del debugging:

```markdown
## El Viaje de dos Números a través del Stack

### Escena 1: Los Números Nacen (main)
\`\`\`c
long a = 10;      // Nace variable 'a' en stack
long b = 25;      // Nace variable 'b' en stack
\`\`\`

### Escena 2: El Llamado (call suma)
El compilador prepara el viaje:
- Carga 'a' (10) en %rdi (primer maletero)
- Carga 'b' (25) en %rsi (segundo maletero)
- Ejecuta CALL (guarda la dirección de retorno)

### Escena 3: La Entrada (suma)
\`\`\`asm
push %rbp         # Guardamos la "zona anterior"
mov %rsp,%rbp     # Marcamos la "nueva zona"
\`\`\`

### Escena 4: La Operación (suma en %rax)
\`\`\`asm
mov %rdi,%rax     # %rax recibe 'a' de %rdi (10)
add %rsi,%rax     # %rax recibe a+b (35)
\`\`\`

### Escena 5: El Regreso (ret)
\`\`\`asm
ret               # La función retorna
\`\`\`

**main ve el resultado en %rax: 35** ✅
```

---

## ✅ Checklist Final

- [ ] README.md mejorado ✅
- [ ] SUGERENCIAS_MEJORA.md ✅
- [ ] RESUMEN_MEJORAS.md ✅
- [ ] Makefile (sugerido)
- [ ] Script de debugging (sugerido)
- [ ] QUICK_REFERENCE.md (sugerido)
- [ ] Screenshots de GDB (muy recomendado)
- [ ] Test script (recomendado)
- [ ] Comentarios en .s files (recomendado)
- [ ] Comparativas visuales (recomendado)

---

**Con estas sugerencias, tu trabajo estaría en nivel profesional de documentación.**

**¡Éxito! 🎓**
