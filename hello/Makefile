CFLAGS = -Wall -g

.PHONY: all clean

%.o: %.asm
	nasm -f elf32 -o $@ $<

all: hello hello_static hello_syscall read_write_syscall

hello: hello.o

hello_static: hello.o
	$(CC) -static -o $@ $^

hello.o: hello.c

hello_syscall: hello_syscall.o
	$(CC) -m32 -o $@ $^

hello_syscall.o: hello_syscall.asm

read_write_syscall: read_write_syscall.o
	$(CC) -m32 -o $@ $^

read_write_syscall.o: read_write_syscall.asm

clean:
	-rm -f hello hello_syscall read_write_syscall
	-rm -f hello.o hello_syscall.o read_write_syscall.o
	-rm -f *~
