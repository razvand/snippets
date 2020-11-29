CFLAGS = -fPIC -fno-stack-protector -Wall -Wextra
LDFLAGS = -pie
LDLIBS = -lbasket

.DEFAULT_GOAL := all

.PHONY: all clean

all: main

main: main.o libbasket.so
	$(CC) $(LDFLAGS) -Wl,-rpath=. -o $@ main.o -L. $(LDLIBS)

main.o: main.c basket.h

libbasket.so: basket.o
	$(CC) -shared -o $@ $^

basket.o: basket.c basket.h

clean:
	-rm -f basket.o main.o
	-rm -f main
	-rm -f libbasket.so
	-rm -f *~
