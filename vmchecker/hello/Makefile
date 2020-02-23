CFLAGS = -Wall -g

.PHONY: all clean pack

all: hello

clean:
	-rm -f hello.o hello
	-rm -f *~

pack:
	zip -r hello.zip hello.c Makefile
