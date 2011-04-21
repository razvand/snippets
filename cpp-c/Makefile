CFLAGS = -Wall -g
LDLIBS = -lstdc++

.PHONY: all clean

all: test

test: test.o add.o

test.o: test.cpp add.h

add.o: add.c add.h

clean:
	-rm -f *~
	-rm -f *.o
	-rm -f test
