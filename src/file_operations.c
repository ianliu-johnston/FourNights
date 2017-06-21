#include "fournights.h"
/**
  * read_file - reads lines from a file, and executes a function on them.
  * @filepath: filepath to read
  * @head: head of a linked list
  * @fxn: pointer to function to enact on char buffer
  * Return: number of bytes read
 **/
size_t read_file(const char *filepath, file_filter_t *file_filter, char *(*fxn)(char *, file_filter_t *))
{
	size_t bytes_read;
	off_t file_offset;
	unsigned int st_size;
	FILE *fd = NULL;

	if (!filepath || !file_filter)
		return(0);
	bytes_read = file_filter->tmp_bufs->bytes_read;
	file_offset = file_filter->tmp_bufs->file_offset;
	st_size = (unsigned int)file_filter->tmp_bufs->file_info.st_size;
	if(st_size == 0)
	{
		fprintf(stderr, "File is empty\n");
		return(0);
	}
	if ((st_size - (int)file_offset) > BIGBUF)
		bytes_read = BIGBUF;
	else
		bytes_read = (size_t)st_size - file_offset;

	if (!(fd = fopen(filepath, "rb")))
		return(0);
	fseek(fd, file_offset, SEEK_SET);
	fread((char *)file_filter->tmp_bufs->plaintext, bytes_read, sizeof(char), fd);
	fclose(fd);
	file_filter->tmp_bufs->file_offset += bytes_read;
	file_filter->tmp_bufs->bytes_read = bytes_read;

	if(fxn)
		fxn(file_filter->tmp_bufs->plaintext, file_filter);
	return (bytes_read);
}

/**
  * write_file - writes the contents of a buffer to a file.
  * @filepath: filepath to write
  * @buffer: buffer to write into the file
  * Return: number of bytes read
 **/
char *write_file(char *buffer, file_filter_t *file_filter)
{
	int buf_size = 0;
	size_t new_ext_len = 0;
	size_t filepath_len = 0;
	size_t bytes_written = 0;
	char *new_ext = ".betty";
	char *filepath = NULL;
	unsigned char *cipher_buf = NULL;
	FILE *fd = NULL;

	filepath = file_filter->tmp_bufs->filepath;
	filepath_len = my_strlen(filepath);
	new_ext_len = my_strlen(new_ext);
	buf_size = file_filter->tmp_bufs->bytes_read;
	/** ENCRYPT **/
	if (file_filter->cipher_flag == 'e')
	{
		if (find_substr_end(filepath, new_ext) == 0)
			my_strncat(filepath, new_ext, filepath_len, new_ext_len);
		if (!(fd = fopen(filepath, "ab+")))
			return(NULL);
		fseek(fd, file_filter->tmp_bufs->file_offset, SEEK_SET);
		cipher_buf = aes_encrypt(file_filter->tmp_bufs->cipher, (unsigned char *)buffer, &buf_size);
	}
	/** DECRYPT **/
	else if (file_filter->cipher_flag == 'd')
	{
		/* TODO: Move these to a new function */
		if (find_substr_end(filepath, new_ext) != 0)
			filepath[filepath_len - new_ext_len] = '\0';
		if (!(fd = fopen(filepath, "ab+")))
			return(NULL);
		fseek(fd, file_filter->tmp_bufs->file_offset, SEEK_SET);
		cipher_buf = aes_decrypt(file_filter->tmp_bufs->cipher, (unsigned char *)buffer, &buf_size);
	}
	if ((bytes_written = fwrite(cipher_buf, buf_size, sizeof(char), fd)) < 1)
	{
		fprintf(stderr, "No bytes written\n");
	}
	free(cipher_buf);
	fclose(fd);
	chmod(filepath, file_filter->tmp_bufs->file_info.st_mode);
	return(buffer);
}
