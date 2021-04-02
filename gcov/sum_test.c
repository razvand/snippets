static unsigned int test_func(void)
{
	unsigned int i, sum;

	sum = 0;
	for (i = 0; i < 100; i++)
		sum += i*i;

	for (i = 0; i < 50; i++)
		sum += i*i*i;

	for (i = 0; i < 80; i++)
		sum += i / 2;

	return sum;
}

static unsigned int test_func2(unsigned int a, unsigned int b)
{
	return a + b;
}

int main(void)
{
	unsigned int i, sum;
	unsigned int ret, ret2;

	sum = 0;
	for (i = 0; i < 100; i++)
		sum += i;

	ret = test_func();
	ret2 = test_func2(10, 20);

	return 0;
}
