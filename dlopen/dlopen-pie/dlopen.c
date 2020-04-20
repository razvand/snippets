#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(void)
{
	void *lib;
	void (*f)(void);

	lib = dlopen("./test", RTLD_NOW);
	if (lib == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	f = (void (*)(void)) dlsym(lib, "do_print");
	if (f == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	f();

	return 0;
}
