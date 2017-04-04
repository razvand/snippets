AS = nasm
LDFLAGS = -m32

.PHONY: all clean

all: stack_access

stack_access: stack_access.o

stack_access.o: stack_access.asm
	$(AS) -f elf32 -o $@ $<

clean:
	-rm -f *~
	-rm -f stack_access.o stack_access
