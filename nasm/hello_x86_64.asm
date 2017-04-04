;
; Simple NASM syntax assembly program for x86_64.
;
; Use commands below to assemble, link and run ($ is the prompt):
;   $ nasm -f elf64 hello_x86_64.asm
;   $ gcc -o hello_x86_64 hello_x86_64.o
;   $ ./hello_x86_64
;   Hello, world!
;

extern printf

section .text

global main

main:
    push rbp
    mov rbp, rsp

    mov rdi, msg
    call printf WRT ..plt

    leave
    ret

section .data
    msg     db  'Hello, world!', 13, 10, 0
