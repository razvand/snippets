#include <stdio.h>

#define min(x, y) ({					\
		typeof(x) _min1 = (x);			\
		typeof(y) _min2 = (y);			\
		(void) (&_min1 == &_min2);		\
		_min1 < _min2 ? _min1 : _min2; })


int main(void)
{
#ifdef SAFE
	unsigned int lulu = 0;
	unsigned int mumu = 1;
#else
	unsigned char lulu = 0;
	unsigned long mumu = 1;
#endif

	min(lulu, mumu);

	return 0;
}
