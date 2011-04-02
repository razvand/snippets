#!/bin/bash

__url="http://www.fundeal.ro/coupon/index/index/ref/bf2905fd31f0b08a7351d19949153adc"
#for url in $(wget -O- "$__url" 2> /dev/null | grep "click aici" | sed 's/^.*\(http:.*\)".*$/\1/'); do
#    wget -O- "$url" 2> /dev/null | grep -A 1 "Cod cupon" | tail -n -1 | sed 's/^.*<strong>\(.*\)<\/strong>.*$/\1/'
#done

wget -O- $(wget -O- "$__url" 2> /dev/null | grep "click aici" | sed 's/^.*\(http:.*\)".*$/\1/') 2> /dev/null | grep -A 1 "Cod cupon" | grep strong | sed 's/^.*<strong>\(.*\)<\/strong>.*$/\1/'
