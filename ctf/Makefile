CFLAGS = -Wall -g
LDFLAGS = -z execstack

.PHONY: all clean

all: shellcode-samples

shellcode-samples: shellcode-samples.o

shellcode-samples.o: shellcode-samples.c

clean:
	-rm -f shellcode-samples shellcode-samples.o *~
