CFLAGS = -Wall
LDLIBS = -lpthread

.PHONY: all clean

all: __thread __thread-static tsd tsd-static

__thread-static: __thread.o
	$(CC) $(LDLFAGS) -static -o $@ $^ $(LDLIBS)

__thread: __thread.o

__thread.o: __thread.c

tsd-static: tsd.o
	$(CC) $(LDLFAGS) -static -o $@ $^ $(LDLIBS)

tsd: tsd.o

tsd.o: tsd.c

clean:
	-rm -f __thread.o __thread __thread-static
	-rm -f tsd.o tsd tsd-static
	-rm -f *~
