.PHONY: all clean

all: dlopen test

dlopen: dlopen.c
	$(CC) -o $@ $^ -ldl

test: test.c
	$(CC) -pie -fPIC -rdynamic -o $@ $^

clean:
	-rm -f dlopen test
	-rm -f *~
