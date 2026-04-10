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

#### dario@dario-N-737R:~/Escritorio/SistemaDeComputacion/SistemaDeComputacion/tp2$ nasm -f elf64 -g calculo.asm -o calculo.o

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

#### (gdb) break sumar_uno 

```
    Punto de interrupción 1 at 0x11b0: file calculo.asm, line 7.
```

#### (gdb) info br

```
        Num     Type           Disp Enb Address            What
        1       breakpoint     keep y   0x00000000000011b0 calculo.asm:7
```
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
#### (gdb) info rax
```
        info orden indefinida: «rax». Intente con «help info»
```

#### (gdb) info  xmm0
```

        info orden indefinida: «xmm0». Intente con «help info»

```
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
#### (gdb) ptype rax

```bash=
        No symbol "rax" in current context.

        (gdb) info register rax
        rax            0x404559999999999a  4631206308062271898
```
#### (gdb) info register xmm
```
        Registro inválido «xmm»
```
#### (gdb) info register xmm0
```bash
        xmm0           {v8_bfloat16 = {0x999a, 0x9999, 0x5999, 0x4045, 0x0, 0x0, 0x0, 0x0}, v8_half = {0x999a, 0x9999, 0x5999, 0x4045, 0x0, 0x0, 0x0, 0x0}, v4_float = {0x9999999a, 0x40455999, 0x0, 0x0}, v2_double = {0x404559999999999a, 0x0}, v16_int8 = {0x9a, 0x99, 0x99, 0x99, 0x99, 0x59, 0x45, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, v8_int16 = {0x999a, 0x9999, 0x5999, 0x4045, 0x0, 0x0, 0x0, 0x0}, v4_int32 = {0x9999999a, 0x40455999, 0x0, 0x0}, v2_int64 = {0x404559999999999a, 0x0}, uint128 = 0x404559999999999a}
```

#### (gdb) p $xmm0.v2_double

```
        $1 = {42.700000000000003, 0}
```

#### (gdb) print $xmm0.v2_double

```
        $2 = {42.700000000000003, 0}
```

#### (gdb) ptype $xmm0.v2_double

```
        type = builtin_type_ieee_double __attribute__ ((vector_size(2)))
```

#### (gdb) Ptype $xmm0.v2_double

```
        orden indefinida: «Ptype». Intente con «help»
```

#### (gdb) x/10gx $rsp

```
        0x7fffffffdae8:	0x000055555555517f	0x404559999999999a
        0x7fffffffdaf8:	0x00007fffffffdc28	0x00007fffffffdba0
        0x7fffffffdb08:	0x00007ffff7c2a1ca	0x00007fffffffdb50
        0x7fffffffdb18:	0x00007fffffffdc28	0x0000000155554040
        0x7fffffffdb28:	0x0000555555555149	0x00007fffffffdc28
```

#### (gdb) stepi

```
        8	    add rax, 1           ; Sumamos 1 -> RAX = 43
```


#### (gdb) info register rax
```

        rax            0x2a                42
```
#### (gdb) x/10gx $rsp

```
        0x7fffffffdae8:	0x000055555555517f	0x404559999999999a
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


#### (gdb) stepi

```
        9	    ret
```

#### (gdb) info register rax

```
        rax            0x2b                43
```

#### (gdb) x/10gx $rsp

```
        0x7fffffffdae8:	0x000055555555517f	0x404559999999999a
        0x7fffffffdaf8:	0x00007fffffffdc28	0x00007fffffffdba0
        0x7fffffffdb08:	0x00007ffff7c2a1ca	0x00007fffffffdb50
        0x7fffffffdb18:	0x00007fffffffdc28	0x0000000155554040
        0x7fffffffdb28:	0x0000555555555149	0x00007fffffffdc28
```


####(gdb) ptype $xmm0.v2_double

```
        type = builtin_type_ieee_double __attribute__ ((vector_size(2)))
```

#### (gdb) stepi
```
        0x000055555555517f in main () at main_debug.c:9
        9	    long resultado = sumar_uno(valor_test);
```
#### (gdb) info register rax
```
        rax            0x2b                43
```
#### (gdb) ptype $xmm0.v2_double
```
        type = builtin_type_ieee_double __attribute__ ((vector_size(2)))
```
#### (gdb) stepi
```
        10	    printf("Resultado final: %ld\n", resultado);
```
#### (gdb) info register rax
```
        rax            0x2b                43
```
#### (gdb) x/10gx $rsp
```

        0x7fffffffdaf0:	0x404559999999999a	0x000000000000002b
        0x7fffffffdb00:	0x00007fffffffdba0	0x00007ffff7c2a1ca
        0x7fffffffdb10:	0x00007fffffffdb50	0x00007fffffffdc28
        0x7fffffffdb20:	0x0000000155554040	0x0000555555555149
        0x7fffffffdb30:	0x00007fffffffdc28	0x0ea35a5894db1af2
```
#### (gdb) info register rax
```
        rax            0x2b                43
```
#### (gdb) stepi
```
        0x0000555555555187	10	    printf("Resultado final: %ld\n", resultado);
        (gdb) x/10gx $rsp
        0x7fffffffdaf0:	0x404559999999999a	0x000000000000002b
        0x7fffffffdb00:	0x00007fffffffdba0	0x00007ffff7c2a1ca
        0x7fffffffdb10:	0x00007fffffffdb50	0x00007fffffffdc28
        0x7fffffffdb20:	0x0000000155554040	0x0000555555555149
        0x7fffffffdb30:	0x00007fffffffdc28	0x0ea35a5894db1af2
```
#### (gdb) info register rax
```
        rax            0x2b                43
```
#### (gdb) stepi
```
        0x000055555555518a	10	    printf("Resultado final: %ld\n", resultado);
```

#### (gdb) x/10gx $rsp

```
        0x7fffffffdaf0:	0x404559999999999a	0x000000000000002b
        0x7fffffffdb00:	0x00007fffffffdba0	0x00007ffff7c2a1ca
        0x7fffffffdb10:	0x00007fffffffdb50	0x00007fffffffdc28
        0x7fffffffdb20:	0x0000000155554040	0x0000555555555149
        0x7fffffffdb30:	0x00007fffffffdc28	0x0ea35a5894db1af2
```

#### (gdb) info register rax
```
        rax            0x2b                43
```







