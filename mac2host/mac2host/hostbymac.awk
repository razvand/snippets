#!/usr/bin/awk -f

BEGIN {
	fire = 0
}

{
	if ($1 == hwaddr) {
		print $2
		fire = 1
		exit 0
	}
}

END {
	if (fire == 1) {	/* match found */
		exit 0
	}
	exit 1
}
