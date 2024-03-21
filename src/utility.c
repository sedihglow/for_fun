#include "utility.h"

void newline_clear(void) /* {{{ */
{
	int i;
	for (i=0; i < 10; ++i) {
		printf("\n\n\n\n\n\n\n\n\n\n");
	}
	fflush(stdout);
} /* end display_clear }}} */

/*
 * TODO:
 * Not a finished function, printouts on error need to be done and just
 * generally check the shit for the generic buffer fill and handling memory on
 * error before exiting the function.
 *
 * current functionality:
 * create a buffer info struct even if len is equal to 0, if len == 0 do not
 * allocate anything in the buffer string buff since no length is given.
 */
struct buffer_info* create_buffer_info(char *inbuff, size_t len) /* {{{ */
{
	struct buffer_info *buffer = CALLOC(struct buffer_info);
	if (errno)
		return NULL;

	buffer->len = len;

	if (len == 0)
		return buffer;

	buffer->buff = CALLOC_ARRAY(char, len);

	if (!buffer->buff)
		return NULL;

	strncpy(buffer->buff, inbuff, len);

	return buffer;
} /* }}} */

/*******************************************************************************
 * Int and Dbl comparison with type limits
 * TODO: Add char unsigned char and unsigned long, see about long long max
 * definition unsure if its in the limits header. Should look at limits header
 * for fun
 *
 * This function needs to be better, the order it checked the tocmp may be wrong
 * or i need to create else trees with it. figure it out later
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

	if (tocmp <= USHRT_MAX) {
		printf("(tocmp = %llu) is < (USHRT_MAX = %u)\n", \
			tocmp, USHRT_MAX);
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
