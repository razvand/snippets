extern sleep

section .text

global main

main:
    push ebp
    mov ebp, esp

    push 10
    call sleep
    add esp, 4

    sub esp, 4
    mov dword [esp], 0x12345678

    sub esp, 1000
    mov dword [esp], 0x87654321
    mov dword [esp-16], 0xabcdef01
    mov dword [esp-24], 0xefcdab78
    mov dword [esp-32], 0x18726354
    ;mov dword [esp-100000], 0x54637281
    sub esp, 100000

    push 10
    call sleep
    add esp, 4

    mov dword [esp-60000], 0x54637281

    push 10
    call sleep
    add esp, 4

    sub esp, 100000
    mov dword [esp-60000], 0x54637281

    push 10
    call sleep
    add esp, 4

    ;;mov dword [esp-127900], 0x88776655

    leave
    ret
