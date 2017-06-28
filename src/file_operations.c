#include "fournights.h"
/**
  * read_file - reads lines from a file into a buffer
  *				and executes a function on them.
  * @path: filepath to read
  * @file_filter: main struct with temporary buffers
  * @fxn: pointer to function to enact on char buffer
  * Return: number of bytes read
 **/
size_t read_file(const char *path,
				 file_filter_t *file_filter,
				 char *(*fxn)(char *, file_filter_t *))
{
	size_t bytes_to_read = 0;
	off_t file_offset;
	unsigned int st_size;
	FILE *fd = NULL;

	if (!path || !file_filter)
		return (0);
	file_offset = file_filter->tmp_bufs->file_offset;
	st_size = (unsigned int)file_filter->tmp_bufs->file_info.st_size;
	if (st_size == 0)
	{
		fprintf(stderr, "File is empty\n");
		return (0);
	}
	if ((st_size - (int)file_offset) > BIGBUF)
		bytes_to_read = BIGBUF;
	else
		bytes_to_read = (size_t)st_size - file_offset;
	fd = fopen(path, "rb");
	if (!fd)
		return (0);
	fseek(fd, file_offset, SEEK_SET);
	fread(file_filter->tmp_bufs->plaintext, bytes_to_read, sizeof(char), fd);
	fclose(fd);
	file_filter->tmp_bufs->file_offset += bytes_to_read;
	file_filter->tmp_bufs->bytes_read = bytes_to_read;
	if (fxn)
		fxn(file_filter->tmp_bufs->plaintext, file_filter);
	return (bytes_to_read);
}

/**
  * write_file - writes the contents of a buffer to a file.
  * @buffer: buffer to write into the file
  * @file_filter: struct with cipher info and temporary buffers
  * Return: number of bytes read
 **/
char *write_file(char *buffer, file_filter_t *file_filter)
{
	size_t new_ext_len, filepath_len = 0;
	char *new_ext =				".betty";
	unsigned char *cipher_buf =	NULL;
	tmp_bufs_t *tmp_bufs =		file_filter->tmp_bufs;
	int bytes_to_write =		file_filter->tmp_bufs->bytes_read;
	char *filepath =			file_filter->tmp_bufs->filepath;
	FILE *fd =					NULL;

	filepath_len = my_strlen(filepath);
	new_ext_len = my_strlen(new_ext);

	if (find_substr_end(filepath, new_ext) == 0)
		my_strncat(filepath, new_ext, filepath_len, new_ext_len);
	else
		filepath[filepath_len - new_ext_len] = '\0';
	fd = fopen(filepath, "ab+");
	if (!fd)
		return (NULL);
	if (file_filter->cipher_flag == 'e') /** ENCRYPT **/
	{
		cipher_buf = aes_encrypt(file_filter->cipher,
								 (unsigned char *)buffer, &bytes_to_write);
		if (file_filter->cipher->buf_len) /** Encrypt one block past final block **/
			tmp_bufs->bytes_read += AES_BLOCK_SIZE - file_filter->cipher->buf_len;
	}
	else if (file_filter->cipher_flag == 'd') /** DECRYPT **/
	{
		cipher_buf = aes_decrypt(file_filter->cipher,
								 (unsigned char *)buffer, &bytes_to_write);
		/* Decrypt all blocks, but write only bits that are not padding */
		if (tmp_bufs->file_offset + BIGBUF > tmp_bufs->file_info.st_size)
			bytes_to_write -= check_padding(cipher_buf, bytes_to_write);
	}
	if (fwrite(cipher_buf, bytes_to_write, sizeof(char), fd) < 1)
		fprintf(stderr, "No bytes written\n");
	free(cipher_buf);
	cipher_buf = NULL;
	fclose(fd);
	fd = NULL;
	return (buffer);
}
