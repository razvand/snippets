#!/bin/bash

for((i=0; i<100; i++)); do
    ./mmap file $((i*1000*100)) $i &
done
