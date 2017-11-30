section .bss
    mybuf: resb 64
    len equ $-mybuf

section .text

global main

main:
    push ebp
    mov ebp, esp

    mov eax, 3 ; 3 is the read syscall
    mov ebx, 0
    mov ecx, mybuf
    mov edx, len
    int 0x80

    mov edx, len ; length of message to be printed
    mov eax, 4 ; 4 is the write syscall index
    ; also found in /usr/include/asm/unistd_32.h (__NR_write)
    mov ebx, 1
    mov ecx, mybuf
    int 0x80

    leave
    ret
