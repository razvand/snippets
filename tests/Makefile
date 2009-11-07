#
# tests Makefile
#

CFLAGS = -Wall -g
SRC = struct_bit.c tcp_new_sock.c

all: endian struct_bit tcp_new_sock

endian: endian.o

struct_bit: struct_bit.o

tcp_new_sock: tcp_new_sock.o

.PHONY: clean

clean:
	-rm -f endian struct_bit tcp_new_sock *~ *.o
