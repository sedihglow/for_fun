/*
 * functions for basic file i/o like add and append to a given file
 */

#include "file.h"
#include "mfuncts.h"

#include <string.h>
#include <errno.h>

#define INBUFF_LEN 512

#define FIO_FAILURE -1
#define FIO_SUCCESS 0

#define PASSED_NULL 134 /* 134 is one value above max errno */

/*
 * Fills the struct file_data's rbuff and rbuff_len.
 * Checks if rbuff is allocated and if it is not it will be allocated to the
 * size of len.
 * If inbuff is NULL but len > 0, rbuff_len is set and rbuff is allocated to
 * the length of len bytes using calloc().
 *
 * returns:
 *	if len == 0:FIO_FAILURE is returned and rbuff/inbuff is not checked.
 *	if an error occurs: errno is returned
 *	if inbuff is NULL and rbuff is allocated: int code 134 (1 higher than
 *							        errno max value)
 *	If sucess:FIO_SUCCESS is returned
 */
int fill_file_rbuff(struct file_data *file, char *inbuff, size_t len)
{
	/* check if len is valid
	 * TODO: If len is set negative when passed theres probably an issue
	 * so there needs to be a limit check if there isnt already in the
	 * c env
	 */
	if (_unlikely(len == 0)) {
		fputs("fill_file_rbuff: len == 0, immediate return", stderr);
		return FIO_FAILURE;
	}

	/* reset rbuff_len to 0 in case reallocation fails (may move this around
	 * unsure at the moment TODO */

	/* check if rbuff needs allocation if already NULL */
	if (_unlikely(file->rbuff == (char*)NULL)) {
		file->rbuff = CALLOC_ARRAY(char, len);
		if (errno) {
			fputs("fill_file_rbuff: rbuff calloc failure", stderr);
			return errno;
		}
	}

	/* if rbuff is allocated see if it matches len already */
	if (_likely(file->rbuff > (char*)NULL)) {
		if (_likely(*file->rbuff_len != len)) {
			/* alloc the new length buffer for rbuff */
			recalloc(&file->rbuff, len);
			if (errno) {
				fputs("fill_file_rbuff: recalloc failure",
				      stderr);
				return errno;
			}
		} else { /* if len is the same set to '\0' */
			memset(file->rbuff, '\0', len);
		}
	} else if (_unlikely(!file->rbuff || file->rbuff < (char*)NULL)) {
			/* rbuff is not notallocated, check rbuff */
			file->rbuff = CALLOC_ARRAY(char, len);
			if (errno) {
				fputs("fill_file_rbuff: rbuff calloc failure",
				      stderr);
				return errno;
			}
	}

	file->rbuff_len = len;

	/* if inbuff is NULL return code int 134 */
	if (_unlikely(!inbuff))
		return PASSED_NULL; /* still success */

	/* if inbuff is not NULL, fill rbuff with inbuff */
	strncpy(file->rbuff, inbuff, len);

	return FIO_SUCCESS;
}

/*
 * return values:
 *	fgets() error: FIO_FAILURE
 *	successful   : FIO_SUCCESS
 *	EOF (testing if on read or during read or both): positive value
 */
int fgets_input(struct file_data *file) /* {{{ */
{
	char inbuff[INBUFF_LEN] = {'\0'};
	size_t len = 0;
	char *fgets_ret = NULL;
	int eof_ret = 0; /* feof() returns non-zero on EOF */

	/* get user input and remove the newline */
	fgets_ret = fgets(inbuff, INBUFF_LEN, file->fp);
	/* NULL on error or EOF */
	if (_unlikely(fgets_ret == (char*)NULL)) {
		/*
		 * TEST: check if EOF, FAILURE should not be returned due to EOF
		 * unless only EOF is encountered
		 */
		eof_ret = feof(file->fp);
		if (_likely(eof_ret > 0)) {
			return eof_ret;
		} else {
			return FIO_FAILURE;
		}
	}

	len = strnlen(inbuff, INBUFF_LEN) - 1;
	if (_likely(inbuff[len] == '\n')) {
		inbuff[len] = '\0';
	} else {
		if (file->fp == stdin) {
			clear_stdin();
		}
	}

	/* fills rbuff and rbuff_len */

	/* TODO: Allocate buffer and fill len */


	return FIO_SUCCESS;
} /* }}} */
