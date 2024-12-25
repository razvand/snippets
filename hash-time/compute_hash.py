#!/usr/bin/env python

import hashlib
import time

NUM_ROUNDS = 10000000

#m = hashlib.md5()
m = hashlib.sha512()
start = time.time()
for i in range(NUM_ROUNDS):
    m.update(b"anaaremere")
stop = time.time()

print("time: ", stop-start)
