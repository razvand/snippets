CFLAGS = -Wall -g
LDLIBS = -lcrypto

.PHONY: all clean

all: gen_ed25519 sign_ed25519 verify_ed25519 ed25519

gen_ed25519: gen_ed25519.o

sign_ed25519: sign_ed25519.o

verify_ed25519: verify_ed25519.o

ed25519: ed25519.o

clean:
	-rm -f gen_ed25519 gen_ed25519.o
	-rm -f sign_ed25519 sign_ed25519.o
	-rm -f verify_ed25519 verify_ed25519.o
	-rm -f ed25519 ed25519.o
	-rm -f private.pem public.pem signature.dat
	-rm -f *~
