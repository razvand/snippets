CFLAGS = -Wall -g -m32
LDFLAGS = -m32
LDLIBS = -lpthread

.PHONY: all clean

all: thread-memory-use-before-after thread-memory-use-before-after-detach use-__thread

thread-memory-use-before-after: thread-memory-use-before-after.o

thread-memory-use-before-after-detach: thread-memory-use-before-after-detach.o

use-__thread: use-__thread.o

clean:
	-rm -f *.o *~
	-rm -f thread-memory-use-before-after
	-rm -f thread-memory-use-before-after-detach
	-rm -f use-__thread
