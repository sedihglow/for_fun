#include "utility.h"


#define INBUFF_LEN 512

/*
 * fill an input buff struct with the characters in the char *buff.
 * If char *buff is NULL then only len is filled into the buffer and the
 * input buffers char* is allocated to length bytes
 */
struct *input_buff init_input_buff(char *buff, size_t len)
{
	struct *input_buff = CALLOC(struct input_buff);
	if (errno)
		errExit("Failed to calloc input_buffer");

	input_buff->len = len;

	input_buff->inbuff = CALLOC_ARRAY(char, len);

	if (buff != NULL)
		strncpy(input_buff->inbuff, buff, len);

	return input_buff;
}

struct *input_buff fgets_input(FILE *fptr)
{
	char inbuff[INBUFF_LEN] = {'\0'};
	size_t len = 0;

	/* get user input and remove the newline */
	fgets(inbuff, INBUFF_LEN, fptr)
	len = strlen(inbuff) - 1;
	if (inbuff[len] == '\n') {
		inbuff[len] = '\0';
	} else {
		CLR_STDIN()
	}

	/* fill an input buffer to return */

	return init_input_buff(inbuff, len + 1);
}


/******************************************************************************
 * stdin/file buff functionality using read system call
 ******************************************************************************/

/* Clears STDIN using read() */
void rd_clr_stdin()
{
	char ch = '\0';
	while (read(STDIN_FILENO, (void*)&ch, BYTE) && ch != '\n' && ch != EOF);
}

void newline_clear(void) /* {{{{ */
{
	int i;
	for (i=0; i < 10; ++i) {
		printf("\n\n\n\n\n\n\n\n\n\n");
	}
	fflush(stdout);
} /* end display_clear }}} */

/*******************************************************************************
 * Int and Dbl comparison with type limits
 * TODO: Add char unsigned char and unsigned long, see about long long max
 * definition unsure if its in the limits header. Should look at limits header
 * for fun
 ******************************************************************************/
void compare_int_limits(unsigned long long tocmp) /* {{{ */
{
	printf("Value being compared: %llu\n", tocmp);

	if (tocmp <= LONG_MAX) {
		printf("(tocmp = %llu) is < (LONG_MAX = %lu)\n", \
			tocmp, LONG_MAX);
	} else {
		printf("(tocmp = %llu) is < (ULONG_MAX = %lu)\n", \
			tocmp, ULONG_MAX);
	}

	if (tocmp <= INT_MAX) {
		printf("(tocmp = %llu) is < (INT_MAX = %u)\n", \
			tocmp, INT_MAX);
	}

	if (tocmp <= UINT_MAX) {
		printf("(tocmp = %llu) is < (UINT_MAX = %u)\n", \
			tocmp, UINT_MAX);
	}
} /* }}} */

void compare_dbl_limits(double tocmp) /* {{{ */
{
	printf("Value being compared: %g\n", tocmp);
	if (tocmp <= FLT_MAX) {
		printf("(tocmp = %f) is < (FLT_MAX = %f)\n", tocmp, FLT_MAX);
	}

	if (tocmp <= DBL_MAX) {
		printf("(tocmp = %g) is < (DBL_MAX = %g)\n", tocmp, DBL_MAX);
	}
} /* }}} */
