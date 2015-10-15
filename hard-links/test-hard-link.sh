#!/bin/bash

touch initial.txt
ln initial.txt hard-link-1.txt
ln initial.txt hard-link-2.txt
echo -n "Number of links is "
stat --format="%h" initial.txt
rm initial.txt hard-link-1.txt hard-link-2.txt
