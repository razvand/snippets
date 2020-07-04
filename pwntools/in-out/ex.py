#!/usr/bin/env python3

import sys
from pwn import *


binary = "./test"
context.binary = binary
#context.log_level = "debug"
e = ELF(binary)

local = True
if local:
    io = process(binary)
else:
    HOST = "141.85.224.102"
    PORT = 31344
    io = remote(HOST, PORT)

io.sendline("10")
msg = io.recvline()
log.info("msg: {}".format(msg))
