CPPFLAGS = -I. -DDEBUG
#CPPFLAGS = -I.
CFLAGS = -Wall -g

.PHONY: all clean

all: test-debug

test-debug.o: test-debug.c debug.h

clean:
	-rm -f *~ *.o test-debug
