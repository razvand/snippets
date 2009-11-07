# libpcap (packet capture) example

CFLAGS = -Wall -g
LDLIBS = -lpcap

all: pcap_test

pcap_test: pcap_test.o

.PHONY: clean

clean:
	-rm -fr pcap_test *.o *~
