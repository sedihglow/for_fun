/*
 * file i/o for basic functionalities like add append etc.
 */

struct file {
	FILE *fp

	/* file and path stuff */
	char   *pathname
	size_t *pathlen
	char   *mode

	/* r/w buffers */
	char *rbuff
	char *wbuff

	/* r/w size/nmemb functionality */
	size_t *rw_size;
	size_t *rw_nmemb;

	/* fseek functionality */
	long *offset;
	int  *whence;

	/* fgetpos() and fsetpos() funcionality */
	fpos_t *pos;
};

inline struct file* open_fp(struct file *file)
{
	return (file->fp = fopen(file->pathname, file->mode));
}

/* returns the number of bytes read */
inline size_t read_fp(struct file *file, size_t size, size_t nmemb)
{
	return (file->rbuff = fread(file->rbuff, size, nmemb, file->fp));
}

/* returns number of bytes written to the file stream */
inline size_t write_fp(struct file *filem, size_t size, sizse_t nmemb)
{
	return (fwrite(file->wbuff, size, nmemb, file->fp));
}

/* returns -1 on error 0 on success */
inline int seek_fp(struct file *file)
{
	return (fseek(file->fp, file->offset, file->whence));
}

inline int getpos_fp(struct file *file)
{

}
