# Guía de Verificación con GDB

## ⚠️ Problema Conocido: Breakpoints en Modo Real (16-bit)

GDB tiene dificultades con breakpoints en código de 16-bit (modo real). La solución es usar un archivo `.gdbinit` que automatiza la conexión y salta directamente a modo protegido (32-bit).

---

## ✅ SOLUCIÓN RECOMENDADA: Usar .gdbinit

El archivo `.gdbinit` está incluido en esta carpeta y automatiza todo.

### Paso 1: Cierra todo lo anterior
```bash
pkill qemu         # Cierra QEMU en Terminal 1
# En GDB: quit    # Sale de GDB en Terminal 2
```

---

### Paso 2: Terminal 1 - Relanza QEMU
```bash
cd modoProtegido
qemu-system-i386 -hda protected_avanzado.img -s -S -no-reboot
```

**Flags explicados:**
- `-s`: Abre servidor GDB en puerto 1234
- `-S`: Pausa al inicio
- `-no-reboot`: Previene reinicio por triple-fault

---

### Paso 3: Terminal 2 - Abre GDB
```bash
cd modoProtegido
gdb -ex "set architecture i386" main_avanzado.o
```

**Automáticamente** el archivo `.gdbinit` ejecutará:
1. ✅ Conectará a QEMU (`:1234`)
2. ✅ Pausará la ejecución
3. ✅ Saltará a `protected_mode` (32-bit)
4. ✅ Mostrará registros y memoria

---

## 🎯 Comandos Útiles en GDB

Una vez que `.gdbinit` finalize, usa estos comandos:

```gdb
(gdb) stepi                          # Ejecutar UNA instrucción
(gdb) info registers                 # Ver EAX, EBX, ECX, EDX, etc.
(gdb) x/4x 0xb8000                  # Leer memoria de video (resultado esperado)
(gdb) x/4x 0xc0000                  # Leer segmento read-only
(gdb) continue                       # Continuar ejecución
(gdb) list                           # Ver código fuente
(gdb) disassemble protected_mode    # Ver código assembler puro
(gdb) quit                           # Salir de GDB
```

---

## 📊 Interpretación de Resultados

### Lectura de Memoria de Video (0xb8000)
```gdb
(gdb) x/4x 0xb8000
0xb8000: 0x0f4f0f4f  0x0f4b0f6b  0x00000000  0x00000000
         ^^^^^^^^    ^^^^^^^^
         "OO"        "kK" en ASCII
```
✅ Si ves estos valores: **Escritura normal funcionó correctamente**

### Lectura de Segmento Read-Only (0xc0000)
```gdb
(gdb) x/4x 0xc0000
0xc0000: 0x00000000  0x00000000  ...
```
❌ Si está en **0x00000000**: La escritura fue **bloqueada** (protección funciona ✓)
✅ Si tiene datos: El segmento **NO es read-only** (revisar descriptor)

---

## ✅ Checklist de Ejecución

- [ ] QEMU corriendo con `-s -S -no-reboot`
- [ ] GDB conectado con arquitectura `i386`
- [ ] `.gdbinit` ejecutó automáticamente
- [ ] Ves registros y código en GDB
- [ ] Ejecutaste `stepi` y ves cambios en registros
- [ ] Leíste memoria 0xb8000 y viste "OO" (0x4f4f)
- [ ] Leíste memoria 0xc0000 (verificaste protección)
