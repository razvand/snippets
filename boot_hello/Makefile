#
# Makefile cheat sheet
#	$< = name of dependency file
#	$@ = name of current target
#

BOOTADDR=0x7c00		# MBR is copied at adress 0x7c00 in RAM

# Create 510 bytes zero filled disk
# Create final bootable image
hello.disk: hello.bin bootcode
	dd count=510 bs=1 if=/dev/zero of=disk 2> /dev/null
	dd conv=notrunc if=hello.bin of=disk 2> /dev/null
	cat disk bootcode > $@
	@echo -e "\nYou may view the output file using\
		\n\t$$ od -x hello.disk"
	
# Creating stripped binary file
hello.bin: hello.out
	objcopy -S -O binary $< $@

# Linking object file to executable (start point is _main)
hello.out: boot_hello.o
	$(LD) -N -Ttext $(BOOTADDR) -e _main -o $@ $<

# Create 2 byte file containing the bootcode (0x55aa)
bootcode:
	echo -en "\x55\xaa" > $@
	

.PHONY: clean hello.disk

clean:
	rm -f hello.disk hello.out hello.bin bootcode disk boot_hello.o *~

