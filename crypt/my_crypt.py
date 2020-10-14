#!/usr/bin/env python

import crypt


PASSWORD = "anaaremere"
ALG_TYPE = "6"
SALT = "abcdefgh"

if ALG_TYPE == "5" or ALG_TYPE == "6":
    SALT = SALT + SALT

enc = crypt.crypt(PASSWORD, "$" + ALG_TYPE + "$" + SALT)
print(enc)
