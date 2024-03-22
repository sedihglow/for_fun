#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * Say we have various types of arrays (not pointers) of X members:
 *	unsigned char charr[X];
 *	unsigned int uintarr[X];
 *	unsigned long ularr[X];
 *
 * Examples plugged into macro:
 *
 *
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/*
 *  The program below demonstrates the use of fread() by parsing /bin/sh
 *  ELF executable in binary mode and printing its magic and class:
 *
 *	   $ ./a.out
 *	   ELF magic: 0x7f454c46
 *	   Class: 0x02
 */
int fread_man_example(void)
{
	FILE *fp = fopen("/bin/sh", "rb");
   	if (!fp) {
   	    perror("fopen");
   	    return EXIT_FAILURE;
   	}

   	unsigned char buffer[4];

   	size_t ret = fread(buffer, ARRAY_SIZE(buffer), sizeof(*buffer), fp);
   	if (ret != sizeof(*buffer)) {
   	    fprintf(stderr, "fread() failed: %zu\n", ret);
   	    exit(EXIT_FAILURE);
   	}

   	printf("ELF magic: %#04x%02x%02x%02x\n", buffer[0], buffer[1],
   	       buffer[2], buffer[3]);

   	ret = fread(buffer, 1, 1, fp);
   	if (ret != 1) {
   	    fprintf(stderr, "fread() failed: %zu\n", ret);
   	    exit(EXIT_FAILURE);
   	}

   	printf("Class: %#04x\n", buffer[0]);

   	fclose(fp);
}


int main(void)
{




	exit(EXIT_SUCCESS);
}
