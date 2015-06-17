CFLAGS = -Wall -g -m32
LDFLAGS = -m32
LDLIBS = -lpthread

.PHONY: all clean

all: thread-memory-use-before-after thread-memory-use-before-after-detach

thread-memory-use-before-after: thread-memory-use-before-after.o

thread-memory-use-before-after-detach: thread-memory-use-before-after-detach.o

clean:
	-rm -f *.o *~ thread-memory-use-before-after
