    .text

.globl _start

# /usr/include/x86_64-linux-gnu/asm/unistd_64.h
.equ __NR_exit, 60

_start:
    call main

    # Call __NR_exit(main_return_value) (system call).
    #
    # Use x86_64 Linux system call convention.
    # https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
    #
    # rdi stores the first system call argument.
    # rax stores the system call id.

    # rax is main return value. Store it in rdi.
    movq %rax, %rdi

    # Store the exit system call id in rax.
    movq $__NR_exit, %rax

    # Do system call.
    syscall
