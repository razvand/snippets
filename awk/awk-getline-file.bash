#!/bin/bash

awk -F ' ' '
BEGIN {
	while (1) {
		if ((getline < "a.txt") == 0)
			break;
		print $0;
	}
	close("a.txt");
}
'
