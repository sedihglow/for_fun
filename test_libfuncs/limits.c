#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void)
{
	printf("ushort max = %hu\n", USHRT_MAX);
	printf("uint max   = %u\n" , UINT_MAX);
	printf("ulong max  = %lu\n", ULONG_MAX);

	printf("uint max   = %d\n" , INT_MAX);
	printf("ulong max  = %ld\n", LONG_MAX);

	return 0;
}
