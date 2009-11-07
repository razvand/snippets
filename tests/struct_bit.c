/*
 * does bitfield syntax affect structure size?
 */

#include <stdio.h>

struct {
	int a:1, b:2, c:3, d:26;
} packed;

struct {
	int a:1;
	int b:2;
	int c:3;
	int d:26;
} unpacked;

int main (void)
{
	printf ("sizeof (packed) = %d, sizeof (unpacked) = %d\n",
			sizeof (packed), sizeof (unpacked));

	return 0;
}
