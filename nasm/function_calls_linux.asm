%include "io.inc"

extern malloc
extern printf
extern strcpy
extern puts
extern free

section .data
    print_format: db "ret: %p", 13, 10, 0
    malloc_ret: dd 0

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    mov al, 0x61
    PRINT_CHAR al
    PRINT_CHAR 13
    PRINT_CHAR 10

    push 100
    call malloc
    add esp, 4

    ; Save malloc pointer value.
    mov dword [malloc_ret], eax

    push eax
    push print_format
    call printf
    add esp, 8

    push print_format
    push dword [malloc_ret]
    call strcpy
    add esp, 8

    push dword [malloc_ret]
    call puts
    add esp, 4

    push dword [malloc_ret]
    call free
    add esp, 4

    leave
    ret
