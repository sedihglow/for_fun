/*
 * functions for basic file i/o like add and append to a given file
 */

#include "file.h"
#include <string.h>
#include <errno.h>

#define INBUFF_LEN 512


char* fill_file_rbuff(struct file_data *file)
{
	if (file->rbuff == NULL) {
		CALLOC_ARRAY(
}

/*
 * Get user input using fgets and fills an input_buff struct with the result
 * excluding the newline from the user input if applicable.
 * Clears stdin if no newline is found (if input goes over INBUFF_LEN)
 */
int fgets_input(struct file_data *file) /* {{{ */
{
	char inbuff[INBUFF_LEN] = {'\0'};
	size_t len = 0;

	/* get user input and remove the newline */
	fgets(inbuff, INBUFF_LEN, file->fp);
	len = strlen(inbuff) - 1;
	if (inbuff[len] == '\n') {
		inbuff[len] = '\0';
	} else {
		clear_stdin();
	}

	/* fills rbuff and rbuff_len */

	/* TODO: Allocate buffer and fill len */


	return errno;
} /* }}} */
