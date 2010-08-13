#!/bin/bash

if test $# -ne 1; then
	echo "Usage: $0 input-file" 1>&2
	exit 1
fi

cat $1 | awk -F ' ' -v len=3 '
BEGIN {
	for (i = 0; i < len; i++)
		for (j = 0; j < len; j++)
			arr[i,j] = 0;
}
{
	if ($1 == "a")
		arr[0,0]++;
	else if ($1 == "b")
		arr[0,1]++;
	else if ($1 == "c")
		arr[0,2]++;
	else if ($1 == "d")
		arr[1,0]++;
	else if ($1 == "e")
		arr[1,1]++;
	else if ($1 == "f")
		arr[1,2]++;
	else if ($1 == "g")
		arr[2,0]++;
	else if ($1 == "h")
		arr[2,1]++;
	else if ($1 == "i")
		arr[2,2]++;
}
END {
	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++)
			printf "%d ", arr[i,j];
		printf "\n";
	}
}'
