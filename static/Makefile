CFLAGS = -Wall

all: hw_dynamic_test hw_static_test

hw_dynamic_test: ld_static_test.o
	$(CC) $^ -o $@

hw_static_test: ld_static_test.o
	$(CC) -static $^ -o $@

.PHONY: clean

clean:
	-rm -f hw_dynamic_test hw_static_test *.o *~
