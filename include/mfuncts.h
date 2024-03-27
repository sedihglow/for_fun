/*
 * implementation of malloc family header file functions for mfuncts.h
 */

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

struct dyn_arr {
	char   *buff;
	size_t *len;
	size_t *size;
};

int recalloc(void **ptr, size_t len);

/* appends to the array */
int dynamic_array_cat(struct dyn_arr *dest, char *src);
