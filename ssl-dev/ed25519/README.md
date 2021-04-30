# ED25519

[ED25519](https://ed25519.cr.yp.to/software.html) (EdDSA) is a signing algorithm based on elliptic curves target at speed without sacrificing security.

This is a test case of generating a private-public key-pair, signing a message (with the private key) and verifying a message (with the public key):
* `gen_ed25519.c` implements the generation of the private-public key pair.
  They are written down in the `private.pem` and `public.pem` files.
* `sign_ed25519.c` implements the signing of a message with `512` `A` characters.
  The signature is writtend down in the `signature.dat` file.
* `verify_ed25519.c` implements the verifying of the `512` `A` characters message with the signature in the `signature.dat` file.

A sample run is below:
```
razvan@yggdrasil:~/.../snippets.git/ssl-dev/ed25519$ ls
gen_ed25519.c  Makefile  README.md  sign_ed25519.c  verify_ed25519.c

razvan@yggdrasil:~/.../snippets.git/ssl-dev/ed25519$ make
cc -Wall -g   -c -o gen_ed25519.o gen_ed25519.c
cc   gen_ed25519.o  -lcrypto -o gen_ed25519
cc -Wall -g   -c -o sign_ed25519.o sign_ed25519.c
cc   sign_ed25519.o  -lcrypto -o sign_ed25519
cc -Wall -g   -c -o verify_ed25519.o verify_ed25519.c
cc   verify_ed25519.o  -lcrypto -o verify_ed25519

razvan@yggdrasil:~/.../snippets.git/ssl-dev/ed25519$ ls
gen_ed25519  gen_ed25519.c  gen_ed25519.o  Makefile  README.md  sign_ed25519  sign_ed25519.c  sign_ed25519.o  verify_ed25519  verify_ed25519.c  verify_ed25519.o

razvan@yggdrasil:~/.../snippets.git/ssl-dev/ed25519$ ./gen_ed25519

razvan@yggdrasil:~/.../snippets.git/ssl-dev/ed25519$ ls
gen_ed25519    gen_ed25519.o  private.pem  README.md     sign_ed25519.c  verify_ed25519    verify_ed25519.o
gen_ed25519.c  Makefile       public.pem   sign_ed25519  sign_ed25519.o  verify_ed25519.c

razvan@yggdrasil:~/.../snippets.git/ssl-dev/ed25519$ ./sign_ed25519

razvan@yggdrasil:~/.../snippets.git/ssl-dev/ed25519$ ls
gen_ed25519    gen_ed25519.o  private.pem  README.md      sign_ed25519    sign_ed25519.o  verify_ed25519.c
gen_ed25519.c  Makefile       public.pem   signature.dat  sign_ed25519.c  verify_ed25519  verify_ed25519.o

razvan@yggdrasil:~/.../snippets.git/ssl-dev/ed25519$ ./verify_ed25519
Message successfully verified.
```
