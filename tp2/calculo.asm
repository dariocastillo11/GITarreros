section .text
    global sumar_uno

sumar_uno:
    ; El valor decimal (42.7) entra por XMM0
    ; cvttsd2si: Convert with Truncation Scalar Double to Signed Integer
    cvttsd2si rax, xmm0  ; Convierte el double (XMM0) a entero (RAX) -> RAX = 42
    add rax, 1           ; Sumamos 1 -> RAX = 43
    ret