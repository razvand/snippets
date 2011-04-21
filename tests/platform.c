#include <stdio.h>

#if defined (_WIN32)
  #define OS_STRING "Windows, 32 bit"
#elif defined (__linux__)
  #define OS_STRING "Linux"
#else
  #error "Unknown OS"
#endif

int main(void)
{
	printf("OS: %s\n", OS_STRING);

	return 0;
}
