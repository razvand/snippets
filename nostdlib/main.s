    .section .rodata
msg:
    .string "Hello, World!\n"

    .text

.globl main

# /usr/include/x86_64-linux-gnu/asm/unistd_64.h
.equ __NR_write, 1
.equ STDOUT_FILENO, 1

main:
    pushq %rbp
    movq %rsp, %rbp

    # Call __NR_write(STDOUT_FILENO, "Hello, World!", 13) (system call).
    #
    # Use x86_64 Linux system call convention.
    # https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
    #
    # rdi stores the first system call argument: STDOUT_FILENO
    # rdx stores the second system call argument: the message
    # r9 stores the first system call argument: the message length
    # rax stores the system call id.

    movq $STDOUT_FILENO, %rdi
    leaq msg(%rip), %rsi
    movq $14, %rdx
    movq $__NR_write, %rax

    # Do system call.
    syscall

    # Return 0.
    xorq %rax, %rax

    leaveq
    ret
