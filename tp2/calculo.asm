section .text
    global sumar_uno ; Hacemos que la función sea visible para C

sumar_uno:
    ; Por convención (System V ABI):
    ; El primer argumento que manda C llega en el registro RDI
    ; El resultado que devolvemos a C debe quedar en el registro RAX
    
    mov rax, rdi    ; Pasamos el número recibido a RAX
    add rax, 1      ; Le sumamos 1
    ret             ; Volvemos a C