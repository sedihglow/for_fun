#include "mfuncts.h"
#include <errno.h>

/*
 * uses calloc to reallocate a buffer to a new size
 */
int recalloc(void **ptr, size_t len)
{
	if (_unlikely(!(*ptr))) {
		*ptr = CALLOC_ARRAY(char, len);
		if (_unlikely(errno))
			return errno;
	}

	/* free if created */
	free(*ptr);

	/* realloc */
	*ptr = CALLOC_ARRAY(char, len);
	if (_unlikely(errno))
		return errno;

	return MFUNC_SUCCESS;
}
