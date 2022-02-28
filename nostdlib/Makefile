CC = gcc-10
LDFLAGS = -nostdlib -nostdinc -static-pie

.PHONY: all clean

all: main

main: start.o main.o

start.o: start.s

main.o: main.s

clean:
	-rm -f start.o main.o
	-rm -f main
	-rm -f *~
