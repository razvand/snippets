CFLAGS = -Wall -g

.PHONY: all move clean

all: move

move: setuid-test
	sudo chown root:root setuid-test
	sudo chmod u+s setuid-test

setuid-test: setuid-test.o

setuid-test.o: setuid-test.c

clean:
	-sudo rm -f setuid-test
	-rm -f *~
	-rm -f *.o
