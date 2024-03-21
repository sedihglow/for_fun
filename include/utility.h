/******************************************************************************
 * filename: utility_sys.h
 *
 * Useful macros and definitions.
 *
 * Written by: James Ross
 *****************************************************************************/

#ifndef _UTL_SYS_H_
#define _UTL_SYS_H_ 1

/* Thesea are just here for reference at the moment
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>
#include <inttypes.h>
#include <errno.h>
#include <pthread.h>

#include <limits.h>
#include <float.h>

#define __USE_MISC 0 // disable misc functionality for now
#ifndef __USE_MISC
	#define __USE_MISC 1 // provide usleep
#endif
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define NDEBUG 1
#include <assert.h>
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <errno.h>
#include <string.h>

#define P_RD 0 // value for a pipe read fd in pipefd[2]
#define P_WR 1 // value for a pip write fd in pipefd[2]

#define SUCCESS 0
#define FAILURE -1

#define RW_END 0

/* GNU compiler native to hint for branch prediction in user space */
#define _likely(x)      __builtin_expect((x), 1)
#define _unlikely(x)    __builtin_expect((x), 0)

/* malloc family allocation macros */
#define SINGLE_NMEMB 1
#define CALLOC(type)             ((type*) calloc(SINGLE_NMEMB, sizeof(type)))
#define CALLOC_VOID(nmemb, size) ((void*) calloc(nmemb, size))
#define CALLOC_ARRAY(type, num)  ((type*) calloc(num, sizeof(type)))

#define my_strdup(dest, src, len)                                              \
{                                                                              \
	dest = CALLOC_ARRAY(char, len);                                        \
	if (_usrlikely(dest))						       \
		memcpy(dest, src, len);					       \
	/* TODO: errhandle if memcpy or calloc fails */			       \
} /* end my_strdup */


/*******************************************************************************
 *
 * stdin buffer handling with read() system calls
 *
 ******************************************************************************/

/*******************************************************************************
 * TODO: Adjust this macro or make an alternate that can call a function with
 *       variable arguments, rather than just one argument. (i.e. free(pntr);)
 *
 * TODO: Find a system or compiler macro, or something, to see if C99 is
 *       supported. If it is not, do not define the macro at all. Programmer
 *       should be aware of it, and for now do not use the macro unless c99 is
 *       supported.
 *
 * Vectorizes the function funct.
 *
 * Will execute every argument into the function.
 * funct can only take 1 argument.
 *
 * -Type is the type of pointer used. (VA_ARGS could be void for example.).
 * -... is a variable argument list.
 *
 * NOTE: Modified to only be used for free
 ******************************************************************************/
#define APPLY_FUNCT(type, funct, ...)                                          \
{                                                                              \
	void *stopper = (int[]){0};					       \
	type **apply_list = (type*[]){__VA_ARGS__, stopper};                   \
	int __i_;                                                              \
									       \
	for (__i_ = 0; apply_list[__i_] != stopper; ++__i_) {                  \
		if (apply_list[__i_])					       \
			(funct)(apply_list[__i_]);                             \
	}                                                                      \
} /* end apply_funct */

/* Apply free to every pointer given in the argument list using apply_funct() */
#define FREE_ALL(...) APPLY_FUNCT(void, free, __VA_ARGS__)

/*******************************************************************************
 * Subtract two timespec structures and place them in a resulting timespec
 * struct.
 *
 * All passed values are pointers of struct timespec.
 ******************************************************************************/
#define _NANO_1SEC (unsigned long long) 1000000000ULL
#define TIMESPEC_SUB(toSubPtr, subByPtr, resRetPtr)                            \
{                                                                              \
	assert((toSubPtr) != NULL && (subByPtr) != NULL && (resRetPtr) != NULL);   \
									       \
	(resRetPtr) -> tv_sec  = ((toSubPtr) -> tv_sec) - \
				 ((subByPtr) -> tv_sec);		       \
	(resRetPtr) -> tv_nsec = ((toSubPtr) -> tv_nsec) - \
				 ((subByPtr) -> tv_nsec);		       \
									       \
	/*
	 * If nano seconds is negetive, need to adjust for carry by adding 1   \
	 * second to nano until nano is no longer negetive or seconds is zero. \
	 */								       \
	while (0 > ((resRetPtr) -> tv_nsec) && 0 < ((resRetPtr) -> tv_sec)) {  \
		--((resRetPtr) -> tv_sec);                                     \
		(resRetPtr) -> tv_nsec = ((resRetPtr) -> tv_nsec) + _NANO_1SEC;\
	}                                                                      \
} /* end TIMESPEC_SUB */

/* input buffer for a dynamically allocated string and its length */
struct buffer_info {
	char *buff;
	size_t len;
};

struct buffer_info* create_buffer_info(char *input, size_t len);

		/* Function prototypes */

void newline_clear(void);

void compare_int_limits(unsigned long long tocmp);
void compare_dbl_limits(double tocmp);
#endif
/************ EOF **************/
