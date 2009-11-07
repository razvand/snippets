.code16		# real mode - 16 bit compatibility mode

# message to print
msg:
	.ascii	"Say hello to my little friend!"

.globl _main	# might as well use the default C start label
_main:

	# all praises to Google :-D
	# http://www.emu8086.com/assembly_language_tutorial_assembler_reference/8086_bios_and_dos_interrupts.html#int10h_00h
	# http://en.wikibooks.org/wiki/X86_Assembly/GAS_Syntax
	# http://linuxgazette.net/issue79/krishnakumar.html

	# set video mode - AH = 0x00
	# AL = 03h -> 80x25. 16 colors. 8 pages
	movb	$0x13,	%al
	movb	$0x00,	%ah
	int	$0x10

	# show standard blinking cursor - AH = 0x01
	movb	$6,	%ch
	movb	$7,	%cl
	movb	$0x01,	%ah
	int	$0x10

	# set cursor position - AH = 0x02
	# DH = row
	# DL = column
	# BH = page
	movb	$5,	%dh
	movb	$10,	%dl
	movb	$0,	%bh
	movb	$0x02,	%ah
	int	$0x10

	# write character - AH = 0x0a
	# AL = character to write
	# BH = page number
	# CX = number of times to write the character
	movb	$0x52,	%al	# because I'm a narcisistic bastard and
				# I love my initial :-)
	movb	$0,	%bh
	movw	$10,	%cx	# print it 10 times
	movb	$0x0a,	%ah
	int	$0x10

	# write string - AH = 0x13
	# AL = write mode (bit 0 - update cursor after writing)
	# BH = page number
	# BL = attribute
	# CX = number of characters in string
	# DH = row
	# DL = column
	# ES:BP = pointes to string to be printed
	movb	$1,	%al
	movb	$0,	%bh
	mov	$0x0f,	%bl	# standard white on black
	movb	$10,	%dl
	movb	$7,	%dh
	movw	$30,	%cx	# message length

	push	%cs
	pop	%es

	movw	$msg,	%bp

	movb	$0x13,	%ah
	int	$0x10

loop:
	nop
	nop
	nop
	jmp	loop
