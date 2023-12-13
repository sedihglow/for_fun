/*
 * file i/o for basic functionalities like add append etc.
 */

#ifndef __FILE_H
#define __FILE_H 0

#include <stdio.h>
#include "utility.h"

struct file_data {
	FILE *fp;

	/* file and path stuff */
	char   *pathname;
	size_t *pathlen;
	char   *mode;

	/* r/w buffers */
	char   *rbuff;
	size_t *rbuff_len; /* includes the '\0' value */
	char   *wbuff;
	size_t *wbuff_len; /* includes the '\0' value */

	/* r/w size/nmemb functionality */
	size_t *rw_size;
	size_t *rw_nmemb;

	/* fseek functionality */
	long *offset; /* offset of place inside the current file stream */
	int  *whence; /* SEEK_SET, SEEK_CUR, SEEK_END */

	/* fgetpos() and fsetpos() funcionality */
	fpos_t *pos;
};

static inline void open_fp(struct file_data *file)
{
	(file->fp = fopen(file->pathname, file->mode));
}

/* returns the number of bytes read */
static inline size_t read_fp(struct file_data *file, size_t size, size_t nmemb)
{
	return (fread(file->rbuff, size, nmemb, file->fp));
}

/* returns number of bytes written to the file stream */
inline size_t write_fp(struct file_data *file, size_t size, size_t nmemb)
{
	return (fwrite(file->wbuff, size, nmemb, file->fp));
}

/* returns -1 on error 0 on success */
static inline int seek_fp(struct file_data *file)
{
	return (fseek(file->fp, *file->offset, *file->whence));
}

static inline int getpos_fp(struct file_data *file)
{
	return (fgetpos(file->fp, file->pos));
}

static inline int setpos_fp(struct file_data *file)
{
	return (fsetpos(file->fp, file->pos));
}

static inline int remove_file(struct file_data *file)
{
	return (remove(file->pathname));
}

/* clears STDIN using getchar() */
static inline void clear_stdin(void)
{
	char _ch = '\0';
	while ((_ch = getchar()) && (_ch != '\n' && _ch != EOF));
}

#endif
