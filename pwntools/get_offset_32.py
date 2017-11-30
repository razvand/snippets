#!/usr/bin/env python

"""
Get return address offset using pwntools.
"""

from pwn import *

need_crash = False

if need_crash == True:
    # Start debugger.
    io = gdb.debug("./vuln_32")

    # Send cyclic pattern to create overflow.
    pattern = cyclic(512)
    io.sendline(pattern)

    pause()

    # Once you get a message such as this, compute the offset.
    # EBP: 0x61616171 ('qaaa')
    # ESP: 0xff8e8e78 ("saaataaauaaavaaawaaaxaaayaaazaabbaabcaabdaabeaabfaabgaa")
    # EIP: 0x61616172 ('raaa')
else:
    # Use value from above step
    eip_value = 0x61616172
    offset = cyclic_find(eip_value)
    log.info("offset: {:d}".format(offset))
