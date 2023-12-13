/*
 * functions for basic file i/o like add and append to a given file
 */

#include "file.h"
#include <string.h>
#include <errno.h>

#define INBUFF_LEN 512

#define FIO_FAILURE -1
#define FIO_SUCCESS 0

/*
 * Fills the struct file_data's rbuff and rbuff_len.
 * Checks if rbuff is allocated and if it is not it will be allocated to the
 * size of len.
 * If inbuff is NULL but len > 0, rbuff_len is set and rbuff is allocated to
 * the length of len bytes using calloc().
 *
 * returns:
 *	if len == 0: IO_FAILURE is returned and rbuff/inbuff is not checked.
 *	if an error occurs: errno is returned
 *	if inbuff is NULL and rbuff is allocated: int code 134 (1 higher than
 *							        errno max value)
 *	If sucess: IO_SUCCESS is returned
 */
int fill_file_rbuff(struct file_data *file, char *inbuff, size_t len)
{
	/* check if len is valid */
	if (_unlikely(len == 0)) {
		fputs("fill_file_rbuff: len == 0, immediate return", stderr);
		return IO_FAILURE;
	}

	/* reset rbuff_len to 0 in case reallocation fails (may move this around
	 * unsure at the moment TODO */

	/* check if rbuff needs allocation if already NULL */
	if (_unlikely(file->rbuff == NULL)) {
		file->rbuff = CALLOC_ARRAY(char, len);
		if (errno)
			return errno;
	}


	/* if rbuff is allocated see if it matches len already */
	if (_likely(file->rbuff > NULL)) {
		if (_likely(file->rbuff_len != len)) {
			file->rbuff_len = len;
			free(file->rbuff);



		}
	}

	/* if rbuff does not match len, reallocate to len bytes */


	/* if inbuff is NULL return code int 134 */

	/* if inbuff is not NULL, fill rbuff with inbuff */

	/* return
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
	if (_unlikely(fgets_ret == NULL)) {
		/*
		 * TEST: check if EOF, FAILURE should not be returned due to EOF
		 * unless only EOF is encountered
		 */
		eof_ret = feof();
		if (_likely(eof_ret > 0)) {
			return eof_ret;
		} else {
			return FIO_FAILURE;
		}
	}

	len = strnlen(inbuff, INBUFF_LEN) - 1;
	if (inbuff[len] == '\n') {
		inbuff[len] = '\0';
	} else {
		clear_stdin();
	}

	/* fills rbuff and rbuff_len */

	/* TODO: Allocate buffer and fill len */


	return FIO_SUCCESS;
} /* }}} */
