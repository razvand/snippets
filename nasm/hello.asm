;
; Simple NASM syntax assembly program for x86 (32 bit).
;
; Use commands below to assemble, link and run ($ is the prompt):
;   $ nasm -f elf32 hello.asm
;   $ gcc -m32 -o hello hello.o
;   $ ./hello
;   Hello, world!
;

extern printf

section .text

global main

main:
    push ebp
    mov ebp, esp

    push msg
    call printf
    add esp, 4

    leave
    ret

section .data
    msg     db  'Hello, world!', 13, 10, 0
