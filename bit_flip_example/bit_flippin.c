#include <stdio.h>
#include <stdlib.h>

#define MASK 0xFFF0FF01

int main()
{
	int manip = 0xFFF1FFFF;
	int flip_res = 0x0;

	flip_res = manip | MASK;
	/* result should be 0xFFF1FFFF */

	printf("manip = %X, mask = %X, flip_res = %X\n", manip, MASK, flip_res);


	exit(EXIT_SUCCESS);
}
