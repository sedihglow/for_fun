/*
 * implementation of malloc family header file functions for mfuncts.h
 */

#include "mfuncts.h"
#include "utility.h"

/*
 * if ptr is NULL allocate
 *
 * TODO: Decide if i want to use this in a free_all type functionality or just
 * do it all here
 *
 * allocated ptr of len bytes
 *
 */

#define MFUNC_FAILURE -1
#define MFUNC_SUCCESS 0

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
	*ptr = CALLOC_ARRAY(char, len)
	if (_unlikely(errno))
		return errno;

	return MFUNC_SUCCESS;
}
