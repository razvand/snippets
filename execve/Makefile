CFLAGS = -Wall -m32 -g
LDFLAGS = -m32

.PHONY: all clean

all: execve_argv

execve_argv: execve_argv.o

execve_argv.o: execve_argv.c

clean:
	-rm -f execve_argv
	-rm -f *.o
	-rm -f *~
