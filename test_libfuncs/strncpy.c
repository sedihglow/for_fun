/*
 * Testing some stuff with string library things or something.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFF_SIZE 32

#define LEN_EQ_CMP "len == "
#define LEN_LT_CMP "len < "
#define LEN_GT_CMP "len > "

#define DEST_CMP_NAME "dest_size"
#define L_EQ_D_STR LEN_EQ_CMP DEST_CMP_NAME
#define L_LT_D_STR LEN_LT_CMP DEST_CMP_NAME
#define L_GT_D_STR LEN_GT_CMP DEST_CMP_NAME

#define SRC_CMP_NAME "src_size"
#define L_EQ_S_STR LEN_EQ_CMP SRC_CMP_NAME
#define L_LT_S_STR LEN_LT_CMP SRC_CMP_NAME
#define L_GT_S_STR LEN_GT_CMP SRC_CMP_NAME

bool test_strncpy(char *dest, char *src, size_t dest_size, size_t src_size,
		  size_t len)
{
	size_t dest_len  = strnlen(dest, dest_size);
	size_t src_len   = strnlen(src, src_size);
	char *ret = NULL;

	if (len == 0)
		return true;

	if (len == dest_size) {
		printf(L_EQ_D_STR "len = %ld, dest_size = %ld\n", len, dest_size);
		ret = strncpy(dest, src, len);

	} else if (len > dest_size) {
		printf(L_GT_D_STR "len = %ld, dest_size = %ld\n", len, dest_size);
		puts("truncating to fit in dest w/ 0x0\n");
		len = dest_size - 1;
		ret = strncpy(dest, src, len);
		puts("post strncpy len > dest_size");
		dest[len] = '\0';

	} else if (len < dest_size) {
		printf(L_LT_D_STR "len = %ld, dest_size = %ld\n", len, dest_size);
		ret = strncpy(dest, src, len);
	}

	if (ret == dest) {
		printf("success: ret = %s, dest = %s, src = %s\n",
			ret, dest, src);
		return true;
	}

	return false;
}

bool util_strncpy(char *dest, char *src, size_t dest_size, size_t src_size,
		  size_t len)
{
	size_t dest_len  = strnlen(dest, dest_size);
	size_t src_len   = strnlen(src, src_size);
	char *ret = NULL;

	if (len == dest_size) {
		printf(L_EQ_D_STR "len = %ld, dest_size = %ld", len, dest_size);
		ret = strncpy(dest, src, len);

	} else if (len > dest_size) {
		printf(L_LT_D_STR "len = %ld, dest_size = %ld", len, dest_size);
		puts("truncating to fit in dest w/ '\0'\n");
		len = dest_size - 1;
		ret = strncpy(dest, src, len);
		dest[len] = '\0';
	}

	if (ret == dest) {
		printf("success: ret = %s, dest = %s, src = %s",
			ret, dest, src);
		return true;
	}

	return false;
}



int main(void)
{

	char dest[BUFF_SIZE] = {"the quick"};
	char src[BUFF_SIZE]  = {"brown fox"};

	size_t cpy_len = 0;

	bool ret = false;

	cpy_len = strlen(src); /* len < dest len */

	ret = test_strncpy(dest, src, 0, BUFF_SIZE, cpy_len);
	if (!ret) {
		fputs("failure, exiting...\n", stderr);
		exit(EXIT_FAILURE);
	}

	ret = test_strncpy(dest, src, BUFF_SIZE, BUFF_SIZE, cpy_len);
	if (!ret) {
		fputs("failure, exiting...\n", stderr);
		exit(EXIT_FAILURE);
	}

	cpy_len = strlen(src); /* == dest len */

	ret = test_strncpy(dest, src, BUFF_SIZE, BUFF_SIZE, cpy_len);
	if (!ret) {
		fputs("failure, exiting...\n", stderr);
		exit(EXIT_FAILURE);
	}



/*
	cpy_len = strlen(src);

	ret = test_strncpy(dest, src, BUFF_SIZE, BUFF_SIZE, cpy_len);
	if (!ret) {
		fputs("failure, exiting...\n", stderr);
		exit(EXIT_FAILURE);
	}
*/


	exit(EXIT_SUCCESS);
}
