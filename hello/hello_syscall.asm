section .data
    hello: db "Hello, World!", 10, 0
    len equ $-hello

section .text

global main

main:
    push ebp
    mov ebp, esp

    mov edx, len ; length of message to be printed
    mov eax, 4 ; 4 is the write syscall index
    ; also found in /usr/include/asm/unistd_32.h (__NR_write)
    mov ebx, 1
    mov ecx, hello
    int 0x80

    leave
    ret
