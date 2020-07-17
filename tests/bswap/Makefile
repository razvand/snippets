CFLAGS = -Wall -nostdinc
LDFLAGS = -static -nostdlib -nodefaultlibs -Wl,-emain

all: bswap

bswap: bswap.o

bswap.o: bswap.c

clean:
	-rm -f *~
	-rm -f bswap.o
	-rm -f bswap
