AS = nasm
ASFLAGS ?= -f elf32
LDFLAGS ?= -m32 -no-pie

OBJS = $(SRCS:.asm=.o)
BINS = $(SRCS:.asm=)

.PHONY: all clean

all: $(BINS)

$(BINS): %: %.o

$(OBJS): %.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	-rm -f *~
	-rm -f $(OBJS)
	-rm -f $(BINS)
