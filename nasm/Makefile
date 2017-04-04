AS = nasm
LDFLAGS = -m32

.PHONY: all clean

all: hello hello_x86_64 flags

hello: hello.o

hello.o: hello.asm
	$(AS) -f elf32 -o $@ $<

hello_x86_64: hello_x86_64.o
	$(CC) -o $@ $^

hello_x86_64.o: hello_x86_64.asm
	$(AS) -f elf64 -o $@ $<

flags: flags.o

flags.o: flags.asm
	$(AS) -f elf32 -o $@ $<

clean:
	-rm -f *~
	-rm -f flags.o flags
	-rm -f hello.o hello
	-rm -f hello_x86_64.o hello_x86_64
