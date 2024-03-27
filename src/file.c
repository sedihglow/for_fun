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


#ifndef COMMENT_OUT
/************************************************
 * Example of using open() fopen() and openat()
 *
 * reference: https://stackoverflow.com/questions/65174086/
 *	      is-there-any-difference-between-filename-max-and-path-max-in-c
 *
 * REAL QUESTIONs: HOW DO I COMMENT THIS OUT PEDANTICALLY IN C89!?
 *	      FUCK.
 *
 *	      CAT ITS YOUR NETWORK, VERSION AND START DATE OF GNUPG . , AND SEND
 *	      IT TO THE FUCKING COPS. IF ITS NOT FUCKED WITH. ITS EPOCH OF
 *	      OPERATING SYSTEMS. I DONT KNOW HOW I GOT THAT BUT I HAVE A
 *	      FEELING,
 *	      ITS CODE R
 *	      CODE R IS REPORT IN FBI DOCS,
 *	      CODE R IS FUCKING CODE RICHIE
 *	      AND THEY KILLED KEVIN MITNICK. FUCK.
 *	      THEY ARE FUCKED.
 *
 *	      ENGINEERING NOW KNOWS, THEY CAN FUCK WITH COMPUTERS, DIRECT,
 *	      THEY ARE STUPID, AND WE ARE THE FUCKING POWER OF THIS PLANET.
 *	      WE ARE SCIENTISTS, ENGINEERS, and motherfucking MATHMATICIANS.
 *
 *	      GET FUCKED.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "myfopen.h"

FILE *my_fopen(const char *filename, const char *mode)
{
    if (strlen(filename) > PATH_MAX) {
        char *work_name = strdup(filename);
        if (!work_name) {
            return NULL; /* cannot malloc */
        }
        char *to_free   = work_name;  /* to free at end */
        int dir_fd      = -1;
        while(strlen(work_name) >= PATH_MAX) {
            char *p = work_name + PATH_MAX - 1;
            while(*p != '/') p--;
            /* p points to the previous '/' to the PATH_MAX limit */
            *p++ = '\0';
            if (dir_fd < 0) {
                dir_fd = open(work_name, 0);
                if (dir_fd < 0) {
                    ERR("open: %s: %s\n", work_name,
                            strerror(errno));
                    free(to_free);
                    return NULL;
                }
            } else {
                int aux_fd = openat(dir_fd, work_name, 0);
                close(dir_fd);
                if (aux_fd < 0) {
                    ERR("openat: %s: %s\n", work_name,
                        strerror(errno));
                    free(to_free);
                    return NULL;
                }
                dir_fd = aux_fd;
            }
            work_name = p;
        }
        /* strlen(work_name) < PATH_MAX,
         * work_name points to the last chunk and
         * dir_fd is the directory to base the real fopen
         */
        int fd = openat(
                dir_fd,
                work_name,
                O_RDONLY); /* this needs to be
                            * adjusted, based on what is
                            * specified in string mode */
        close(dir_fd);
        if (fd < 0) {
            fprintf(stderr, "openat: %s: %s\n",
                    work_name, strerror(errno));
            free(to_free);
            return NULL;
        }
        free(to_free);
        return fdopen(fd, mode);
    }
    return fopen(filename, mode);
}
#endif

/* file_open will allocate a file_data struct if one is not passed
 * if struct file_data pointer is NULL
 * - a newly allocated file_data struct is returned
 * - the same returned struct is set to the function argument *file
 * if struct file_data pointer is passed
 * - the file_data pointer passed is returned
 *
 */
struct file_data* file_fopen(struct file_data *fdata, char *pathname, /* #{{{ */
			     char *mode)
{
	size_t len = 0;

	/* if no pathname nothing to open */
	if (!pathname) {
		return -1;
	}

	if (!fdata) {
		file = file_data_init(file);
	}

	if (!mode) {
		/* mode is null so fopen should just use default */
		fprintf(stderr, "file_fopen: no mode provided, setting to"
				"DFLT_FMODE\n");
	} else { /* mode is passed in function argument */
		/* check if valid mode is given */
		len = strnlen(mode, file->mode_maxlen);
	}


	/* greater than two isnt valid for custom mode options, which isnt
	 * a huge deal at the moment anyway. The length 2 string for the mode
	 * is only for file pointers.
	 *
	 * we should do octal too, 000 etc like chmod as an option or as meta
	 * data, putting in struct real fast
	 */
	if (len > 2, len == 0)
		return FIO_FAILURE;

	strncpy(fdata->mode, mode, fdata->mode_maxlen);

	fdata->mode_len = len;

	fdata->pathlen = pathlen;
} /* }}} */

/*
 * - Allocates with calloc the file_data struct
 * - Allocates members of the file_data struct that get an initalized value
 *   and size which is not handled in other functions for file operations.
 *
 * Members that get allocated and their initalization values:
 *
 */
struct file_data* file_data_init(void) /* #{{{ */
{
	struct file_data *fdata;

	/*
	 * calloc of the alloc family sets the allocated data to 0 by default,
	 * setting all the fdata member to NULL for us.
	 */
	fdata = CALLOC(struct file_data);

	fdata->fp = NULL; /* file pointer, fr/w fopen etc. */
	fdata->fd = NULL; /* file descriptor, r/w, open, fp -> fd */

	/* file and path stuff */
	fdata->pathname
	fdata->pathlen = 0;
	fdata->mode = 0;

	/* TODO:
	 * mode max length may differ if not using the fp family but wanting
	 * to use some other implementation, by default it is set to
	 * fmode right now, on init see about manually setting it for
	 * fd's and custom values for the struct,
	 *
	 * Might be in a helper function for initialization
	 */
	fdata->mode_maxlen = FMODE_S_MAX;

	/* r/w buffers */
	fdata->rbuff = 0;
	fdata->rbuff_len = 0; /* includes the '\0' value */
	fdata->wbuff = 0;
	fdata->wbuff_len = 0; /* includes the '\0' value */

	/* fr/fw size/nmemb functionality, (man 3 fread()) */
	fdata->rw_size = 0;
	fdata->rw_nmemb = 0;

	return fdata;
} /* }}} */

/*
 * Fills the struct file_data's rbuff and rbuff_len.
 * Checks if rbuff is allocated and if it is not it will be allocated to the
 * size of len.
 *
 * NOTE: might adjust this a little bit and require inbuff since i could
 * potentially just do the functionality of the NULL inbuff outside of the
 * function.
 * If inbuff is NULL but len > 0, rbuff_len is set and rbuff is allocated to
 * the length of len bytes using calloc() and not filled with anything from
 * inbuff. This allows the function to be used as an realloc or initial alloc
 * for rbuff to be used outside of the function.
 *
 * returns:
 *	if len == 0:FIO_FAILURE is returned and rbuff/inbuff is not checked.
 *	if an error occurs: errno is returned
 *	if inbuff is NULL and rbuff is allocated: int code 134 (1 higher than
 *	errno max value), this lets us know rbuff was allocated.
 *
 *	If sucess: FIO_SUCCESS is returned
 */
int fill_file_rbuff(struct file_data *fdata, char *inbuff, size_t len) /* #{{{ */
{
	/* check if len is valid
	 * TODO: If len is set negative when passed theres probably an issue
	 * so there needs to be a limit check if there isnt already in the
	 * c env
	 */
	if (_unlikely(len <= 0)) {
		fputs("fill_file_rbuff: len == 0, immediate return", stderr);
		return FIO_FAILURE;
	}

	/* reset rbuff_len to 0 in case reallocation fails (may move this around
	 * unsure at the moment TODO */

	/* check if rbuff needs allocation if already NULL */
	if (_unlikely(fdata->rbuff == (char*)NULL)) {
		fdata->rbuff = CALLOC_ARRAY(char, len);
		if (errno) {
			fputs("fill_file_rbuff: rbuff calloc failure", stderr);
			return errno;
		}
	}

	/* if rbuff is allocated see if it matches len already */
	if (_likely(fdata->rbuff > (char*)NULL)) {
		if (_likely(*fdata->rbuff_len != len)) {
			/* alloc the new length buffer for rbuff */
			recalloc((void**)&(fdata->rbuff), len);
			if (errno) {
				fputs("fill_file_rbuff: recalloc failure",
				      stderr);
				return errno;
			}
		} else { /* if len is the same set to '\0' */
			memset(fdata->rbuff, '\0', len);
		}

		/*
		 * Check if pointer is null or address is negative, if the
		 * pointer is allocated properly then the adderess will not be
		 * less than NULL. If it is something messed up setting the
		 * address. If it is a negative address free wont do anything
		 * proper because its a negative address so in this case either
		 * way we have no option other than to allocate even if it is a
		 * negative address.
		 *
		 * NOTE: Possibly print something letting us know its negative,
		 * look at more information on what happens if something sets an
		 * address to NULL or make sure its handled if a negative
		 * address is passed on purpose and print an error.
		 */
	} else if (_unlikely(fdata->rbuff < (char*)NULL)) {
			/* rbuff is not not allocated, check rbuff */
			fdata->rbuff = CALLOC_ARRAY(char, len);
			if (errno) {
				fputs("fill_file_rbuff: rbuff calloc failure",
				      stderr);
				return errno;
			}
	} else {
		/*
		 * what rbuff address in a virtual address space is set for a
		 * pointer on free might be negative after a free
		 */
		free(fdata->rbuff);
	}

	/*
	 * ensure rbuff_len is allocated to hold the length of the newly
	 * allocated rbuff for the file
	 *
	 * TODO: Decide how i want to handle erroring out here with an error
	 * code of my own or figure out how this would be handled outside of the
	 * function. Might make a flag to show if realloc was called and base it
	 * off that.
	 */
	if (_unlikely(fdata->rbuff_len <= (size_t*)NULL)) {
		fdata->rbuff_len = CALLOC(size_t);
		if (errno) {
			fputs("fill_file_rbuff: rbuff_len alloc failure.",
			      stderr);
			return errno;
		}
	}

	*fdata->rbuff_len = len;

	/* if inbuff is NULL return code int 134 */
	if (_unlikely(!inbuff))
		return PASSED_NULL; /* still success */

	/* if inbuff is not NULL, fill rbuff with inbuff */
	strncpy(fdata->rbuff, inbuff, len);

	return FIO_SUCCESS;
} /* }}} */

/*
 * return values:
 *	fgets() error: FIO_FAILURE
 *	successful   : FIO_SUCCESS
 *	EOF (testing if on read or during read or both): positive value
 */
int fgets_input(struct file_data *fdata) /* {{{ */
{
	char inbuff[INBUFF_LEN] = {'\0'};
	size_t len = 0;
	char *fgets_ret = NULL;
	int eof_ret = 0; /* feof() returns non-zero on EOF */

	/* get user input and remove the newline */
	fgets_ret = fgets(inbuff, INBUFF_LEN, fdata->fp);
	/* NULL on error or EOF */
	if (_unlikely(fgets_ret == (char*)NULL)) {
		/*
		 * TEST: check if EOF, FAILURE should not be returned due to EOF
		 * unless only EOF is encountered
		 */
		eof_ret = feof(fdata->fp);
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
		if (fdata->fp == stdin) {
			clear_stdin();
		}
	}

	/* fills rbuff and rbuff_len */
	++len; /* move len to size instead of index used to check \n */
	fill_file_rbuff(fdata, inbuff, len);

	return FIO_SUCCESS;
} /* }}} */
