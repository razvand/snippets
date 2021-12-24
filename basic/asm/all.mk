AS = nasm
ASFLAGS = -f elf64
ASFLAGS_32 = -f elf32
LDFLAGS = -pie -dynamic
LDFLAGS_32 = -m32 -pie -dynamic
LDFLAGS_NOPIE = -no-pie -dynamic
LDFLAGS_32_NOPIE = -m32 -no-pie -dynamic
LDFLAGS_STATIC = -no-pie -static
LDFLAGS_32_STATIC = -m32 -no-pie -static

OBJS = $(SRCS:.asm=.o) \
	$(SRCS:.asm=_32.o) \
	$(SRCS:.asm=_nopie.o) \
	$(SRCS:.asm=_32_nopie.o) \
	$(SRCS:.asm=_static.o) \
	$(SRCS:.asm=_32_static.o) \

BINS = $(OBJS:.o=)


.PHONY: all clean

all: $(BINS)

%_32_static: %_32_static.o
	$(CC) $(LDFLAGS_32_STATIC) -o $@ $^

%_32_static.o: %_32.asm
	$(AS) $(ASFLAGS_32) -o $@ $<

%_static: %_static.o
	$(CC) $(LDFLAGS_STATIC) -o $@ $^

%_static.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

%_32_nopie: %_32_nopie.o
	$(CC) $(LDFLAGS_32_NOPIE) -o $@ $^

%_32_nopie.o: %_32.asm
	$(AS) $(ASFLAGS_32) -o $@ $<

%_nopie: %_nopie.o
	$(CC) $(LDFLAGS_NOPIE) -o $@ $^

%_nopie.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

%_32: %_32.o
	$(CC) $(LDFLAGS_32) -o $@ $^

%_32.o: %_32.asm
	$(AS) $(ASFLAGS_32) -o $@ $<

$(SRCS:.asm=): %: %.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	-rm -f *~
	-rm -f $(BINS)
	-rm -f $(OBJS)
