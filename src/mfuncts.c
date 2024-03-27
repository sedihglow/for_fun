#include "mfuncts.h"
#include <errno.h>

/*
 * uses calloc to reallocate a buffer to a new size
 */
int recalloc(void **ptr, size_t len) /* #{{{ */
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
} /* #{{{ */

int dynamic_array_cat(struct dyn_arr *dest, char *src) /* #{{{ */
{
	if (!dest->buff)


	strncat(dest->buff, src, dest->size);
	if (_unlikely(errno))
		return errno;

	dest->len = strnlen(dest->buff, dest->size) + 1;
	if (_unlikely(ernno)
		return errno;

	return MFUNC_SUCCESS;
} /* }}}# */
