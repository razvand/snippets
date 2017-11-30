.PHONY: all clean

all: vuln vuln_32 vuln_pie vuln_static vuln_stripped

vuln: CFLAGS = -Wall -g -fno-stack-protector -Wno-unused-function -mpreferred-stack-boundary=4 -fno-PIC
vuln: LDFLAGS = -no-pie
vuln: vuln.o

vuln_32: CFLAGS = -Wall -m32 -g -fno-stack-protector -Wno-unused-function -mpreferred-stack-boundary=2 -fno-PIC
vuln_32: LDFLAGS = -no-pie -m32
vuln_32: vuln_32.o

vuln_pie: CFLAGS = -Wall -g -fno-stack-protector -Wno-unused-function -mpreferred-stack-boundary=4 -fPIC
vuln_pie: LDFLAGS = -pie
vuln_pie: vuln_pie.o

vuln_static: CFLAGS = -Wall -g -fno-stack-protector -Wno-unused-function -mpreferred-stack-boundary=4 -fno-PIC
vuln_static: LDFLAGS = -no-pie -static
vuln_static: vuln_static.o

vuln_stripped: CFLAGS = -Wall -g -fno-stack-protector -Wno-unused-function -mpreferred-stack-boundary=4 -fno-PIC
vuln_stripped: LDFLAGS = -no-pie
vuln_stripped: vuln_stripped.o
	$(CC) $(LDFLAGS) -o $@ $^
	strip $@

%.o: vuln.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *~
	-rm -f vuln.o vuln_32.o vuln_pie.o
	-rm -f vuln vuln_32 vuln_pie vuln_static vuln_stripped
