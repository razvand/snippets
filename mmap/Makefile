CFLAGS = -Wall -g
LDLIBS = -lrt

.PHONY: all clean

all: mmap file dual-mapping mmap-overalloc mmap-ftruncate mmap-duration

file:
	truncate -s 100M file

clean:
	rm -f *.o *~ mmap file dual-mapping mmap-overalloc mmap-ftruncate
