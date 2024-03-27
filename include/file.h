/*
 * file i/o for basic functionalities like add append etc.
 */

#ifndef __FILE_H
#define __FILE_H 0

#include <stdio.h>
#include "utility.h"

#define FMODE_S_MAX 3 /* includes '/0' */

/*	   Table reference for mode permissions fopen() and open()
 *	      ┌─────────────┬───────────────────────────────┐
 *	      │fopen() mode │ open() flags					│
 *	      ├─────────────┼───────────────────────────────┤
 *	      │	    r	    │ O_RDONLY						│
 *	      ├─────────────┼───────────────────────────────┤
 *	      │	    w	    │ O_WRONLY | O_CREAT | O_TRUNC  │
 *	      ├─────────────┼───────────────────────────────┤
 *	      │	    a	    │ O_WRONLY | O_CREAT | O_APPEND │
 *	      ├─────────────┼───────────────────────────────┤
 *	      │	    r+	    │ O_RDWR						│
 *	      ├─────────────┼───────────────────────────────┤
 *	      │	    w+	    │ O_RDWR | O_CREAT | O_TRUNC    │
 *	      ├─────────────┼───────────────────────────────┤
 *	      │	    a+	    │ O_RDWR | O_CREAT | O_APPEND   │
 *	      └─────────────┴───────────────────────────────┘
 */

#define DFLT_FMODE RP_FMODE /* Used if no mode provided on opening file */
#define R_FMODE  'r'  /* read only, begining of file */
#define RP_FMODE "r+" /* r/w, begining of file */
#define W_FMODE  'w'  /* Truncate file to zero len or create text file for
					   * writing. begining of file */
#define WP_FMODE "w+" /* r/w, file is created if non existant, otherwise
					   * truncated. begining of file */
#define A_FMODE  'a'  /* append (at EOF), file created if does not exist. */
#define AP_FMODE "a+" /* read + append (at EOF) Output is always appended to
					   * the end of the file.  POSIX is silent on what
					   * the initial read position is when using this mode.
					   * For glibc, the initial file position
					   * for reading is at the beginning of the file, but for
					   * Android/BSD/MacOS, the initial file position
				       * for reading is at the end of the file.
					   */


struct file_data {
	FILE *fp; /* file pointer, fr/w fopen etc. */
	int   fd; /* file descriptor, r/w, open, fp -> fd */

	/* file and path stuff */
	char    *pathname;
	size_t  *pathlen;
	char    *mode;
	uint8_t *oct_mode

	size_t *mode_len;
	size_t *mode_maxlen; /* includes '\0' */

	/* r/w buffers */
	char   *rbuff;
	size_t *rbuff_len; /* includes the '\0' value */
	char   *wbuff;
	size_t *wbuff_len; /* includes the '\0' value */

	/* r/w size/nmemb argument functionality (man 3 fread()) */
	size_t *rw_tsize; /* sizeof(type) of buffer for fr/fw */
	size_t *rw_nmemb; /* number of array elements for fr/fw buffer, size*len */

	/* fseek functionality */
	long *offset; /* offset of place inside the current file stream */
	int  *whence; /* SEEK_SET, SEEK_CUR, SEEK_END */

	/* fgetpos() and fsetpos() funcionality */
	fpos_t *pos;
};

static inline void open_fp(struct file_data *fdata)
{
	return (fdata->fp = fopen(fdata->pathname, fdata->mode));
}

/* returns the number of bytes read */
static inline size_t read_fp(struct file_data *fdata, size_t size, size_t nmemb)
{
	return (fread(fdata->rbuff, size, nmemb, fdata->fp));
}

/* returns number of bytes written to the file stream */
inline size_t write_fp(struct file_data *fdata, size_t size, size_t nmemb)
{
	return (fwrite(fdaa->wbuff, size, nmemb, fdata->fp));
}

/* returns -1 on error 0 on success */
static inline int seek_fp(struct file_data *fdata)
{
	return (fseek(fdata->fp, *fdata->offset, *fdata->whence));
}


static inline int getpos_fp(struct file_data *fdata)
{
	return (fgetpos(fdata->fp, fdata->pos));
}

static inline int setpos_fp(struct file_data *fdata)
{
	return (fsetpos(fdata->fp, fdata->pos));
}

static inline int remove_file(struct file_data *fdata)
{
	return (remove(fdata->pathname));
}

/* clears STDIN using getchar() */
static inline void clear_stdin(void)
{
	char _ch = '\0';
	while ((_ch = getchar()) && (_ch != '\n' && _ch != EOF));
}
#endif

int fgets_input(struct file_data *fdata);

/* */
int fill_file_rbuff(struct file_data *fdata, char *inbuff, size_t len);
int file_fopen(struct *file_data, char *pathname, size_t pathlen, char *mode);

/* test functions */
