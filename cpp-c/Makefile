CFLAGS = -Wall -g -m32
CXXFLAGS = -Wall -g -m32
LDFLAGS = -m32
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
