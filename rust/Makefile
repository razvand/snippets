RUSTC = rustc

.PHONY: all clean

all: hello

hello: hello.rs
	$(RUSTC) -o $@ $^

clean:
	-rm -f hello
	-rm -f *~
