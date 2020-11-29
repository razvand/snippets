CFLAGS = -fPIC -fno-stack-protector -Wall -Wextra
LDFLAGS = -nostdlib -nostdinc -pie
LDLIBS = -lbasket
LD.SO = /lib/x86_64-linux-gnu/ld-linux-x86-64.so.2

.DEFAULT_GOAL := all

.PHONY: all clean

all: main

main: start.o main.o libbasket.so
	$(LD) -e_start -pie -dynamic-linker=$(LD.SO) -rpath=. -o $@ start.o main.o -L. $(LDLIBS)
#	$(CC) $(LDFLAGS) -Wl,-e_start -o $@ start.o main.o -L. $(LDLIBS)

start.o: start.s

main.o: main.c basket.h

libbasket.so: basket.o
	$(LD) -shared -o $@ $^
#	$(CC) $(LDFLAGS) -shared -o $@ $^

basket.o: basket.c basket.h

clean:
	-rm -f start.o basket.o main.o
	-rm -f main
	-rm -f libbasket.so
	-rm -f *~
