CFLAGS = -Wall -g

.PHONY: all clean

all: mmap file dual-mapping mmap-overalloc mmap-ftruncate

file:
	truncate -s 100M file

clean:
	rm -f *.o *~ mmap file dual-mapping mmap-overalloc mmap-ftruncate
