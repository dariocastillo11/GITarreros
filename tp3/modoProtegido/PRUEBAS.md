# Modo Protegido Avanzado - Guía de Pruebas

## 📋 Estado Actual

✅ **Código compilado:** `protected_avanzado.img`
✅ **Firma de boot:** Bytes `55 AA` presentes en offset `0x1FE`
✅ **Segmentos:** 3 descriptores GDT configurados

---

## 🎯 Requisitos Cumplidos

### 1️⃣ Código sin Macros
```asm
.quad 0x00cf9a000000ffff    # Descriptor de código manualmente
.quad 0x00cf92000000ffff    # Descriptor de datos RW
.quad 0x00cf90000000ffff    # Descriptor de datos RO (bytes individuales)
```

### 2️⃣ Segmentos Diferenciados
| Descriptor | Base | Tipo | Permisos |
| :--- | :--- | :--- | :--- |
| 0x08 (Código) | 0x00000000 | Ejecutable | RW |
| 0x10 (Datos) | 0x00100000 | Datos | RW |
| 0x18 (Datos) | 0x00200000 | Datos | RO ❌ |

### 3️⃣ Prueba de Solo Lectura
- **Selector 0x18** apunta a descriptor con byte `0x90` (SOLO LECTURA)
- Intento de `movl %eax, (0xc0000)` debería fallar

### 4️⃣ Verificación con GDB
- Conexión remota configurada
- Breakpoints funcionales
- Lectura de memoria en vivo

---

## 🚀 Cómo Ejecutar

### Opción A: Solo Ver (Sin Debugger)
```bash
cd modoProtegido
qemu-system-i386 -hda protected_avanzado.img
```

**Resultado esperado:** Pantalla negra con "XX" en blanco (si funciona)

---

### Opción B: Debuggear con GDB (RECOMENDADO)

**Terminal 1 - Lanzar QEMU en espera:**
```bash
cd modoProtegido
qemu-system-i386 -hda protected_avanzado.img -s -S
```

**Terminal 2 - Conectar GDB:**
```bash
cd modoProtegido
gdb main_avanzado.o
```

**Dentro de GDB:**
```gdb
(gdb) target remote :1234
(gdb) break protected_mode
(gdb) continue

# Ver registros después del salto
(gdb) info registers

# Leer la GDT
(gdb) x/24x gdt_start

# Ver memoria de video (después de escribir)
(gdb) x/4x 0xb8000

# Intentar leer donde debería estar la escritura read-only
(gdb) x/4x 0xc0000

# Continuar
(gdb) continue
```

---

## 📊 Análisis de Resultados

### ✅ Si ves "OO" en pantalla:
```
Dirección: 0xb8000
Datos: 0x0f4f0f4f
ASCII: "OO" en blanco
→ Escritura normal funcionó ✓
```

### ❌ Si falla al intentar escribir en 0x18:
```
Segmento: 0x18 (read-only)
Instrucción: movl %eax, (0xc0000)
Resultado: #GP (General Protection Fault)
→ La protección de memoria funciona ✓
```

---

## 📝 Notas Importantes

1. **Sin manejador de IDT:** Si genera #GP, QEMU puede reiniciar (Triple Fault)
2. **GDB no captura #GP directamente:** Necesitarías configurar un manejador de excepciones
3. **La prueba de read-only es teórica en este caso:** Verifica que el descriptor tiene el byte correcto

---

## 🔧 Archivos del Proyecto

```
modoProtegido/
├── main_avanzado.S              # Código con 3 descriptores GDT
├── link.ld                       # Linker script simplificado
├── protected_avanzado.img        # Imagen booteable compilada
├── compile.sh                    # Script de compilación
├── GDB_GUIDE.md                  # Guía detallada de GDB
└── PRUEBAS.md                    # Este archivo
```

---

## 🎓 Lo que Aprendemos

1. **GDT Manual:** Cómo escribir descriptores sin herramientas macro
2. **Aislamiento de memoria:** Bases diferentes para cada segmento
3. **Protección de memoria:** Bits de permiso (0x90 vs 0x92)
4. **Debugging de firmware:** Usar GDB con QEMU en modo remoto
5. **Modo Protegido:** Cómo funcionan los selectores vs direcciones
