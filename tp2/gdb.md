#### dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ cat main_debug.c

```c++
        #include <stdio.h>

        // Declaramos la función de assembler
        extern long sumar_uno(double n);

        int main() {
            double valor_test = 42.7;
            printf("--- Iniciando prueba para GDB ---\n");
            long resultado = sumar_uno(valor_test);
            printf("Resultado final: %ld\n", resultado);
            return 0;

```
# Compilo mi programa asm 
#### dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ nasm -f elf64 -g calculo.asm -o calculo.o

# Compilo mi programa c que simula el de python para poder debugear
#### dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ gcc -g main_debug.c calculo.o -o programa_debug
```bash=
        /usr/bin/ld: warning: calculo.o: missing .note.GNU-stack section implies executable stack
        /usr/bin/ld: NOTE: This behaviour is deprecated and will be removed in a future version of the linker

```
#### dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/

SistemaDeComputacion/tp2$ ls
```bash=
            app.py       calculo.o  gdb.md      interfaz.o     main.c        programa_debug
            calculo.asm  env        interfaz.c  libcalculo.so  main_debug.c  README.md
```
# Ejecuto prueba GDB
#### dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ gdb ./programa_debug

```bash=
            GNU gdb (Ubuntu 15.0.50.20240403-0ubuntu1) 15.0.50.20240403-git
            Copyright (C) 2024 Free Software Foundation, Inc.
            License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
            This is free software: you are free to change and redistribute it.
            There is NO WARRANTY, to the extent permitted by law.
            Type "show copying" and "show warranty" for details.
            This GDB was configured as "x86_64-linux-gnu".
            Type "show configuration" for configuration details.
            For bug reporting instructions, please see:
            <https://www.gnu.org/software/gdb/bugs/>.
            Find the GDB manual and other documentation resources online at:
                <http://www.gnu.org/software/gdb/documentation/>.

            For help, type "help".
            Type "apropos word" to search for commands related to "word"...
            Reading symbols from ./programa_debug...

```
# Comando li para ver codigo 
#### (gdb) li


```c++
        1	#include <stdio.h>
        2	
        3	// Declaramos la función de assembler
        4	extern long sumar_uno(double n);
        5	
        6	int main() {
        7	    double valor_test = 42.7;
        8	    printf("--- Iniciando prueba para GDB ---\n");
        9	    long resultado = sumar_uno(valor_test);
        10	    printf("Resultado final: %ld\n", resultado);

```
#### (gdb) li
```c++
        11	    return 0;
        12	}

```
#### (gdb) li

```
        End of the file was already reached, use "list ." to list the current location again
```
# Poner un breakpoint en una parte de codigo
#### (gdb) break sumar_uno 

```
    Punto de interrupción 1 at 0x11b0: file calculo.asm, line 7.
```

# Mostrar todos mis brackpoint
#### (gdb) info br

```
        Num     Type           Disp Enb Address            What
        1       breakpoint     keep y   0x00000000000011b0 calculo.asm:7
```

# Correr GDB. Se detiene en los breackpoint
#### (gdb) run

```bash=
        Starting program: /home/dario/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2/programa_debug 

        This GDB supports auto-downloading debuginfo from the following URLs:
        <https://debuginfod.ubuntu.com>
        Enable debuginfod for this session? (y or [n]) y
        Debuginfod has been enabled.
        To make this setting permanent, add 'set debuginfod enabled on' to .gdbinit.
        Downloading separate debug info for system-supplied DSO at 0x7ffff7fc3000
        [Depuración de hilo usando libthread_db enabled]                                           
        Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
        --- Iniciando prueba para GDB ---

        Breakpoint 1, sumar_uno () at calculo.asm:7
        7	    cvttsd2si rax, xmm0  ; Convierte el double (XMM0) a entero (RAX) -> RAX = 42

```
# Puedo ver manual de GDB . 
#### (gdb) help info
```bash=
        info, inf, i
        Orden genérica para mostrar cosas sobre el programa que esta siendo depurado.

        List of info subcommands:

        info address -- Describe where symbol SYM is stored.
        info all-registers -- List of all registers and their contents, for selected stack frame.
        info args -- All argument variables of current stack frame or those matching REGEXPs.
        info auto-load -- Print current status of auto-loaded files.
        info auxv -- Mostrar el vector auxiliar inferior.
        info bookmarks -- Status of user-settable bookmarks.
        info breakpoints, 
        info b -- Status of specified breakpoints (all user-settable breakpoints if no argument).
        info checkpoints -- ID de los actualmente conocidos puntos de comprobación.
        info classes -- All Objective-C classes, or those matching REGEXP.
        info common -- Print out the values contained in a Fortran COMMON block.
        info connections -- Target connections in use.
        info copying -- Condiciones para redistribuir copias de GDB.
        info dcache -- Print information on the dcache performance.
        info display -- Expressions to display when program stops, with code numbers.
        info exceptions -- List all Ada exception names.
        info extensions -- Todos los nombres de archivo asociados con un lenguaje fuente.
        info files -- Names of targets and files being debugged.
        info float -- Print the status of the floating point unit.
        info frame, info f -- All about the selected stack frame.
        info frame-filter -- List all registered Python frame-filters.
        info functions -- All function names or those matching REGEXPs.
        info guile, info gu -- Prefix command for Guile info displays.
        info inferiors -- Print a list of inferiors being managed.
        info line -- Core addresses of the code for a source line.
        info locals -- All local variables of current stack frame or those matching REGEXPs.
        info macro -- Show the definition of MACRO, and it's source location.
        info macros -- Show the definitions of all macros at LINESPEC, or the current source location.
        info main -- Get main symbol to identify entry point into program.
        info mem -- Memory region attributes.
        info missing-debug-handlers -- GDB command to list missing debug handlers.
        info module -- Print information about modules.
        info modules -- All module names, or those matching REGEXP.
        info os -- Show OS data ARG.
        info pretty-printer -- GDB command to list all registered pretty-printers.
        info probes -- Show available static probes.
        info proc -- Show additional information about a process.
        --Type <RET> for more, q to quit, c to continue without paging--
        info program -- Estado de ejecución del programa.
        info record, info rec -- Info record options.
        info registers, 
        info r -- List of integer registers and their contents, for selected stack frame.
        info scope -- List the variables local to a scope.
        info selectors -- All Objective-C selectors, or those matching REGEXP.
        info sharedlibrary, info dll -- Estado de bibliotecas de objeto compartidas.
        info signals, info handle -- What debugger does when program gets various signals.
        info skip -- Display the status of skips.
        info source -- Información sobre el archivo fuente actual.
        info sources -- All source files in the program or those matching REGEXP.
        info stack, info s -- Backtrace of the stack, or innermost COUNT frames.
        info static-tracepoint-markers -- List target static tracepoints markers.
        info symbol -- Describe what symbol is at location ADDR.
        info target -- Names of targets and files being debugged.
        info tasks -- Provide information about all known Ada tasks.
        info terminal -- Print inferior's saved terminal status.
        info threads -- Display currently known threads.
        info tracepoints, 
        info tp -- Status of specified tracepoints (all tracepoints if no argument).
        info tvariables -- Status of trace state variables and their values.
        info type-printers -- GDB command to list all registered type-printers.
        info types -- All type names, or those matching REGEXP.
        info unwinder -- GDB command to list unwinders.
        info variables -- All global and static variable names or those matching REGEXPs.
        info vector -- Print the status of the vector unit.
        info vtbl -- Show the virtual function table for a C++ object.
        info warranty -- Varios tipos de garantía que no tiene.
        info watchpoints -- Status of specified watchpoints (all watchpoints if no argument).
        info win -- List of all displayed windows.
        info xmethod -- GDB command to list registered xmethod matchers.

        Type "help info" followed by info subcommand name for full documentation.
        Type "apropos word" to search for commands related to "word".
        Type "apropos -v word" for full documentation of commands related to "word".
        Command name abbreviations are allowed if unambiguous.

```
#### (gdb) li

```c++

        2	    global sumar_uno
        3	
        4	sumar_uno:
        5	    ; El valor decimal (42.7) entra por XMM0
        6	    ; cvttsd2si: Convert with Truncation Scalar Double to Signed Integer
        7	    cvttsd2si rax, xmm0  ; Convierte el double (XMM0) a entero (RAX) -> RAX = 42
        8	    add rax, 1           ; Sumamos 1 -> RAX = 43
        9	    ret
```
rax es un registro de enteros, y xmm0 un registre de double. cvttsd2si convierte el doble a entero.

# Abreviaciones: RUN r, NEXT n, STEP s, BREACKPOINT br
#### (gdb) r


```bash=
        The program being debugged has been started already.
        Start it from the beginning? (y or n) y
        Starting program: /home/dario/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2/programa_debug 
        [Depuración de hilo usando libthread_db enabled]
        Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
        --- Iniciando prueba para GDB ---

        Breakpoint 1, sumar_uno () at calculo.asm:7
        7	    cvttsd2si rax, xmm0  ; Convierte el double (XMM0) a entero (RAX) -> RAX = 42

```
# Ver contenido de un registro
#### (gdb) ptype rax

```bash=
        No symbol "rax" in current context.

        (gdb) info register rax
        rax            0x404559999999999a  4631206308062271898
```


# Ver informacion de un registro
#### (gdb) info register xmm0
```bash
        xmm0{  
                v8_bfloat16 = {0x999a, 0x9999, 0x5999, 0x4045, 0x0, 0x0, 0x0, 0x0},

                v8_half = {0x999a, 0x9999, 0x5999, 0x4045, 0x0, 0x0, 0x0, 0x0}, 

                v4_float = {0x9999999a, 0x40455999, 0x0, 0x0}, 

                v2_double = {0x404559999999999a, 0x0}, #El que nos interesa ver

                v16_int8 = {0x9a, 0x99, 0x99, 0x99, 0x99, 0x59, 0x45, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, 

                v8_int16 = {0x999a, 0x9999, 0x5999, 0x4045, 0x0, 0x0, 0x0, 0x0}, 

                v4_int32 = {0x9999999a, 0x40455999, 0x0, 0x0},

                v2_int64 = {0x404559999999999a, 0x0}, 

                uint128 = 0x404559999999999a
        }

```
# imprimo con print o p el valor del double almacenado en xmm0
#### (gdb) p $xmm0.v2_double

```bash
        $1 = {42.700000000000003, 0} # Vemos que es nuestro 42.7 double
```

#### (gdb) print $xmm0.v2_double

```
        $2 = {42.700000000000003, 0}
```
# Veo tipo de dato del registro con ptype
#### (gdb) ptype $xmm0.v2_double

```bash
        type = builtin_type_ieee_double __attribute__ ((vector_size(2)))
        # nos da la info de registro. Un vectr de tamaño 2.
```
# Veo la info de tipo de dato de funciones con Ptype
#### (gdb) Ptype $xmm0.v2_double

```bash
        orden indefinida: «Ptype». Intente con «help»
        # No funciona porque no e suna funcion, es un registro
```
# Veo el stack Pila. Direcciones de retorno.
#### (gdb) x/10gx $rsp

```bash 
        0x7fffffffdae8:	0x000055555555517f	0x404559999999999a
                        #direccion memoria a retornar : 0x000055555555517f

        0x7fffffffdaf8:	0x00007fffffffdc28	0x00007fffffffdba0

        0x7fffffffdb08:	0x00007ffff7c2a1ca	0x00007fffffffdb50

        0x7fffffffdb18:	0x00007fffffffdc28	0x0000000155554040

        0x7fffffffdb28:	0x0000555555555149	0x00007fffffffdc28
```
### Cuando C llama a ASM  o primero que hace es anotar la direccion de memoria a la cual debe retornar cuando termine


# Nos entramos dentro de la funcion sumar_uno. Codigo ASM. Con stepi
#### (gdb) stepi

```bash 
        8	    add rax, 1           ; Sumamos 1 -> RAX = 43
```


#### (gdb) info register rax
```bash 

        rax            0x2a                42 #rax tiene un 42
```
# Compruebo que pila no cambio, tampoco el valor del registro aun:

#### (gdb) x/10gx $rsp

```bash
        0x7fffffffdae8:	0x000055555555517f	0x404559999999999a
        #Mismo valor
        0x7fffffffdaf8:	0x00007fffffffdc28	0x00007fffffffdba0
        0x7fffffffdb08:	0x00007ffff7c2a1ca	0x00007fffffffdb50
        0x7fffffffdb18:	0x00007fffffffdc28	0x0000000155554040
        0x7fffffffdb28:	0x0000555555555149	0x00007fffffffdc28
```

#### (gdb) ptype $xmm0.v2_double

```
        type = builtin_type_ieee_double __attribute__ ((vector_size(2)))
```

#### (gdb) p $xmm0.v2_double

```
        $3 = {42.700000000000003, 0}
```

# Ejecuto sigueinte instruccion. 
#### (gdb) stepi

```
        9	    ret
```

# Visualizo porque deberia cambiar la pila y datos del registros:
#### (gdb) info register rax

```bash
        rax            0x2b                43 # Ahora rax vale 43. Le sumamos el 1
```

#### (gdb) x/10gx $rsp

```bash
        0x7fffffffdae8:	0x000055555555517f	0x404559999999999a
        # La Pila sigue igual . Porque aun no nos salimos del ASM

        0x7fffffffdaf8:	0x00007fffffffdc28	0x00007fffffffdba0
        0x7fffffffdb08:	0x00007ffff7c2a1ca	0x00007fffffffdb50
        0x7fffffffdb18:	0x00007fffffffdc28	0x0000000155554040
        0x7fffffffdb28:	0x0000555555555149	0x00007fffffffdc28
```

# Siguiente instruccion nos volvemos a C. Retomamos la direccion de la pila:

#### (gdb) stepi
```bash
        0x000055555555517f in main () at main_debug.c:9
        9	    long resultado = sumar_uno(valor_test);
```
#### (gdb) info register rax
```bash
        rax            0x2b                43 #rax quedo con 43 
```

#### (gdb) x/10gx $rsp
```bash

        0x7fffffffdaf0:	0x404559999999999a	0x000000000000002b
        # Pila cambio de valor , vemos que todas las direcciones de la derecha se desplazaron hacia la izquierda

        0x7fffffffdb00:	0x00007fffffffdba0	0x00007ffff7c2a1ca
        0x7fffffffdb10:	0x00007fffffffdb50	0x00007fffffffdc28
        0x7fffffffdb20:	0x0000000155554040	0x0000555555555149
        0x7fffffffdb30:	0x00007fffffffdc28	0x0ea35a5894db1af2
```
---



Podemos ver que cuando c llego a la funcion sumar_uno de asm guardo en el stack la direccion
 ***0x000055555555517f***


Esto lo podemos ver con OBJDUMP haciendo un desamblado de nuestro programa y visualizando los call:
Omitimos el resto de desamlado  y nos quedamos con main y sumar_uno

---
```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ objdump -d programa_debug 
```
---

# Lo importante la funcion main y sumar_uno:

```bash
0000000000001149 <main>:
    1149:       f3 0f 1e fa             endbr64
    114d:       55                      push   %rbp
    114e:       48 89 e5                mov    %rsp,%rbp
    1151:       48 83 ec 10             sub    $0x10,%rsp
    1155:       f2 0f 10 05 e3 0e 00    movsd  0xee3(%rip),%xmm0        
    115c:       00 
    115d:       f2 0f 11 45 f0          movsd  %xmm0,-0x10(%rbp)
    1162:       48 8d 05 9f 0e 00 00    lea    0xe9f(%rip),%rax        
    1169:       48 89 c7                mov    %rax,%rdi
    116c:       e8 bf fe ff ff          call   1030 <puts@plt>
    1171:       48 8b 45 f0             mov    -0x10(%rbp),%rax
    1175:       66 48 0f 6e c0          movq   %rax,%xmm0

                                        #call va a la direccion 11b0 que es donde vive sumar_uno
    117a:       e8 31 00 00 00          call   11b0 <sumar_uno>

        #siguiente direccion 117f es guardada el stack
    117f:       48 89 45 f8             mov    %rax,-0x8(%rbp)
    1183:       48 8b 45 f8             mov    -0x8(%rbp),%rax
    1187:       48 89 c6                mov    %rax,%rsi
    118a:       48 8d 05 99 0e 00 00    lea    0xe99(%rip),%rax       
    1191:       48 89 c7                mov    %rax,%rdi
    1194:       b8 00 00 00 00          mov    $0x0,%eax
    1199:       e8 a2 fe ff ff          call   1040 <printf@plt>
    119e:       b8 00 00 00 00          mov    $0x0,%eax
    11a3:       c9                      leave
    11a4:       c3                      ret
    11a5:       66 2e 0f 1f 84 00 00    cs nopw 0x0(%rax,%rax,1)
    11ac:       00 00 00 
    11af:       90                      nop
```

```bash
00000000000011b0 <sumar_uno>: # direccion 11bo donde llamo el call

    11b0:       f2 48 0f 2c c0          cvttsd2si %xmm0,%rax
    11b5:       48 83 c0 01             add    $0x1,%rax
    11b9:       c3                      ret
    # retorna y cambia el stack saca la direccion que guardo 117f para volver al punto de partida
```
---

# Otras herramientas:
---
# strace
```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ strace ./programa_debug
``` 

```bash
execve("./programa_debug", ["./programa_debug"], 0x7ffd9bc905f0 /* 80 vars */) = 0
brk(NULL)                               = 0x5fef861fe000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x71fb0afb8000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No existe el archivo o el directorio)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=111611, ...}) = 0
mmap(NULL, 111611, PROT_READ, MAP_PRIVATE, 3, 0) = 0x71fb0af9c000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220\243\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
fstat(3, {st_mode=S_IFREG|0755, st_size=2125328, ...}) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2170256, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x71fb0ac00000
mmap(0x71fb0ac28000, 1605632, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x71fb0ac28000
mmap(0x71fb0adb0000, 323584, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b0000) = 0x71fb0adb0000
mmap(0x71fb0adff000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1fe000) = 0x71fb0adff000
mmap(0x71fb0ae05000, 52624, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x71fb0ae05000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x71fb0af99000
arch_prctl(ARCH_SET_FS, 0x71fb0af99740) = 0
set_tid_address(0x71fb0af99a10)         = 78611
set_robust_list(0x71fb0af99a20, 24)     = 0
rseq(0x71fb0af9a060, 0x20, 0, 0x53053053) = 0
mprotect(0x71fb0adff000, 16384, PROT_READ) = 0
mprotect(0x5fef51315000, 4096, PROT_READ) = 0
mprotect(0x71fb0aff8000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x71fb0af9c000, 111611)          = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
getrandom("\x62\x60\xc7\x5b\xdc\x27\xb7\x84", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x5fef861fe000
brk(0x5fef8621f000)                     = 0x5fef8621f000
write(1, "--- Iniciando prueba para GDB --"..., 34--- Iniciando prueba para GDB ---
) = 34
write(1, "Resultado final: 43\n", 20Resultado final: 43
)   = 20
exit_group(0)                           = ?
+++ exited with 0 +++
```
---


# valgrid
```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ valgrind ./programa_debug
```
```bash
==78981== Memcheck, a memory error detector
==78981== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==78981== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==78981== Command: ./programa_debug
==78981== 
--- Iniciando prueba para GDB ---
Resultado final: 43
==78981== 
==78981== HEAP SUMMARY:
==78981==     in use at exit: 0 bytes in 0 blocks
==78981==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==78981== 
==78981== All heap blocks were freed -- no leaks are possible
==78981== 
==78981== For lists of detected and suppressed errors, rerun with: -s
==78981== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
---

# nm
```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ nm programa_debug | grep sumar_uno
```

```bash
00000000000011b0 T sumar_uno
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ nm programa_debug 
000000000000037c r __abi_tag
0000000000004010 B __bss_start
0000000000004010 b completed.0
                 w __cxa_finalize@GLIBC_2.2.5
0000000000004000 D __data_start
0000000000004000 W data_start
0000000000001090 t deregister_tm_clones
0000000000001100 t __do_global_dtors_aux
0000000000003db8 d __do_global_dtors_aux_fini_array_entry
0000000000004008 D __dso_handle
0000000000003dc0 d _DYNAMIC
0000000000004010 D _edata
0000000000004018 B _end
00000000000011bc T _fini
0000000000001140 t frame_dummy
0000000000003db0 d __frame_dummy_init_array_entry
0000000000002108 r __FRAME_END__
0000000000003fb0 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
0000000000002048 r __GNU_EH_FRAME_HDR
0000000000001000 T _init
0000000000002000 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U __libc_start_main@GLIBC_2.34
0000000000001149 T main
                 U printf@GLIBC_2.2.5
                 U puts@GLIBC_2.2.5
00000000000010c0 t register_tm_clones
0000000000001060 T _start
00000000000011b0 T sumar_uno
0000000000004010 D __TMC_END__
```
---

# readelf
```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ readelf -l programa_debug
```

```bash
El tipo del fichero elf es DYN (Position-Independent Executable file)
Entry point 0x1060
There are 13 program headers, starting at offset 64

Encabezados de Programa:
  Tipo           Desplazamiento     DirVirtual         DirFísica
                 TamFichero         TamMemoria          Opts   Alineación
  PHDR           0x0000000000000040 0x0000000000000040 0x0000000000000040
                 0x00000000000002d8 0x00000000000002d8  R      0x8
  INTERP         0x0000000000000318 0x0000000000000318 0x0000000000000318
                 0x000000000000001c 0x000000000000001c  R      0x1
      [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]
  LOAD           0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000650 0x0000000000000650  R      0x1000
  LOAD           0x0000000000001000 0x0000000000001000 0x0000000000001000
                 0x00000000000001c9 0x00000000000001c9  R E    0x1000
  LOAD           0x0000000000002000 0x0000000000002000 0x0000000000002000
                 0x000000000000010c 0x000000000000010c  R      0x1000
  LOAD           0x0000000000002db0 0x0000000000003db0 0x0000000000003db0
                 0x0000000000000260 0x0000000000000268  RW     0x1000
  DYNAMIC        0x0000000000002dc0 0x0000000000003dc0 0x0000000000003dc0
                 0x00000000000001f0 0x00000000000001f0  RW     0x8
  NOTE           0x0000000000000338 0x0000000000000338 0x0000000000000338
                 0x0000000000000020 0x0000000000000020  R      0x8
  NOTE           0x0000000000000358 0x0000000000000358 0x0000000000000358
                 0x0000000000000044 0x0000000000000044  R      0x4
  GNU_PROPERTY   0x0000000000000338 0x0000000000000338 0x0000000000000338
                 0x0000000000000020 0x0000000000000020  R      0x8
  GNU_EH_FRAME   0x0000000000002048 0x0000000000002048 0x0000000000002048
                 0x000000000000002c 0x000000000000002c  R      0x4
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RWE    0x10
  GNU_RELRO      0x0000000000002db0 0x0000000000003db0 0x0000000000003db0
                 0x0000000000000250 0x0000000000000250  R      0x1

 Asignación de Sección a Segmento:
  Segmento Secciones...
   00     
   01     .interp 
   02     .interp .note.gnu.property .note.gnu.build-id .note.ABI-tag .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt 
   03     .init .plt .plt.got .text .fini 
   04     .rodata .eh_frame_hdr .eh_frame 
   05     .init_array .fini_array .dynamic .got .data .bss 
   06     .dynamic 
   07     .note.gnu.property 
   08     .note.gnu.build-id .note.ABI-tag 
   09     .note.gnu.property 
   10     .eh_frame_hdr 
   11     
   12     .init_array .fini_array .dynamic .got 
```
---


# ltrace
```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ ltrace ./programa_debug
```


```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ ltrace ./programa_debug
puts("--- Iniciando prueba para GDB --"...--- Iniciando prueba para GDB ---
)                                                                                                                  = 34
printf("Resultado final: %ld\n", 43Resultado final: 43
)                                                                                                                         = 20
+++ exited (status 0) +++
```
---

# gdb -  backtrace
```bash
dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ gdb ./programa_debug 
```

```bash                                                                                                
Breakpoint 1, sumar_uno () at calculo.asm:7
7           cvttsd2si rax, xmm0  ; Convierte el double (XMM0) a entero (RAX) -> RAX = 42
(gdb) bt
#0  sumar_uno () at calculo.asm:7
#1  0x000055555555517f in main () at main_debug.c:9
(gdb) n
8           add rax, 1           ; Sumamos 1 -> RAX = 43
(gdb) bt
#0  sumar_uno () at calculo.asm:8
#1  0x000055555555517f in main () at main_debug.c:9
(gdb) n
9           ret
(gdb) bt
#0  sumar_uno () at calculo.asm:9
#1  0x000055555555517f in main () at main_debug.c:9
(gdb) n
main () at main_debug.c:10
10          printf("Resultado final: %ld\n", resultado);
(gdb) bt
#0  main () at main_debug.c:10
(gdb) 
```
---