#!/usr/bin/awk -f

{
	if ($3 < 200 && $3 > 100)
		printf "%s (%d)\n", $1, $3;
}
