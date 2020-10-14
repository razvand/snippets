#!/bin/bash

PASSWORD="anaaremere"
ALG_TYPE="sha-512" # des, md5, sha-256
SALT="abcdefgh"

if test "$ALG_TYPE" = "sha-256" -o "$ALG_TYPE" = "sha-512"; then
    SALT="$SALT$SALT"
fi

mkpasswd -m "$ALG_TYPE" -S "$SALT" "$PASSWORD"
