Whenever a kernel thread tries to access user space data it uses the page table of the previous process.

In our module we used a simple conifguration where a busybox process is almost always the "previous" process. We read the first 64 bytes from the .text area of the busybox process and print it. We actually read the start of the busybox ELF executable file now mapped into memory in the .text area of the process, as expected.

Below is a sample output from the kernel module:
    [   17.537644] Thread has been created.
    [   17.543878] Thread will read from address 0x08048000
    [   17.544946] Data has been read. Dumping hex:
    [   17.545613] \x7f\x45\x4c\x46\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x03\x00\x01\x00\x00\x00\xe4\xc1\x11\x08\x34\x00\x00\x00\xe8\xd1\x1c\x00\x00\x00\x00\x00\x34\x00\x20\x00\x05\x00\x28\x00\x1c\x00\x1b\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x80\x04\x08
    [   17.564427]

And a dump of the start of the busybox ELF executable file:

    $ xxd -l 64 -g 1 busybox
    0000000: 7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00  .ELF............
    0000010: 02 00 03 00 01 00 00 00 e4 c1 11 08 34 00 00 00  ............4...
    0000020: e8 d1 1c 00 00 00 00 00 34 00 20 00 05 00 28 00  ........4. ...(.
    0000030: 1c 00 1b 00 01 00 00 00 00 00 00 00 00 80 04 08  ................
