section .text

global main

main:
    push ebp
    mov ebp, esp

    mov al, 127
    mov bl, 100
    add al, bl

    mov al, 130
    mov bl, 130
    add al, bl

    mov al, 200
    mov bl, 100
    add al, bl

    leave
    ret
