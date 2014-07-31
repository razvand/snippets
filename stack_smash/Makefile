CFLAGS = -Wall -g

.PHONY: all clean

all: stack-smash-no-protector stack-smash-protector

stack-smash-no-protector: stack-smash.c
	gcc -Wall -g -o $@ $^

stack-smash-protector: stack-smash.c
	gcc -Wall -g -fstack-protector -o $@ $^

clean:
	-rm -f stack-smash-protector stack-smash-no-protector
	-rm -f *~
	-rm -f *.o
