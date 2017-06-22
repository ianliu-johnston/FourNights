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
	size_t bytes_to_read;
	off_t file_offset;
	unsigned int st_size;
	FILE *fd = NULL;

	if (!filepath || !file_filter)
		return(0);
	bytes_to_read = 0;
	file_offset = file_filter->tmp_bufs->file_offset;
	st_size = (unsigned int)file_filter->tmp_bufs->file_info.st_size;
	if(st_size == 0)
	{
		fprintf(stderr, "File is empty\n");
		return(0);
	}
	if ((st_size - (int)file_offset) > BIGBUF)
		bytes_to_read = BIGBUF;
	else
		bytes_to_read = (size_t)st_size - file_offset;
	if (!(fd = fopen(filepath, "rb")))
		return(0);
	fseek(fd, file_offset, SEEK_SET);
	fread((char *)file_filter->tmp_bufs->plaintext, bytes_to_read, sizeof(char), fd);
	fclose(fd);
	file_filter->tmp_bufs->file_offset += bytes_to_read;
	file_filter->tmp_bufs->bytes_read = bytes_to_read;
	if(fxn)
		fxn(file_filter->tmp_bufs->plaintext, file_filter);
	return (bytes_to_read);
}
/*
	printf("\nFile offset %d, bytes to read: %d, st_size: %d, ftell: %lu\n", (int)file_offset, (int) bytes_to_read, (int) st_size, ftell(fd));
	printf("READING at %p\n", (void *)file_filter->tmp_bufs->plaintext);
	write(1, (char *)file_filter->tmp_bufs->plaintext, 200);
	putchar('\n');
*/

/**
  * write_file - writes the contents of a buffer to a file.
  * @filepath: filepath to write
  * @buffer: buffer to write into the file
  * Return: number of bytes read
 **/
char *write_file(char *buffer, file_filter_t *file_filter)
{
	int buf_size = 0;
	size_t new_ext_len, filepath_len = 0;
	char *new_ext = ".betty";
	char *filepath = NULL;
	unsigned char *cipher_buf = NULL;
	FILE *fd = NULL;

	filepath = file_filter->tmp_bufs->filepath;
	filepath_len = my_strlen(filepath);
	new_ext_len = my_strlen(new_ext);
	buf_size = file_filter->tmp_bufs->bytes_read;

	if (find_substr_end(filepath, new_ext) == 0)
		my_strncat(filepath, new_ext, filepath_len, new_ext_len);
	else
		filepath[filepath_len - new_ext_len] = '\0';
	if (!(fd = fopen(filepath, "ab+")))
		return(NULL);
	if (file_filter->cipher_flag == 'e') /** ENCRYPT **/
		cipher_buf = aes_encrypt(file_filter->cipher, (unsigned char *)buffer, &buf_size);
	else if (file_filter->cipher_flag == 'd') /** DECRYPT **/
	{
		cipher_buf = aes_decrypt(file_filter->cipher, (unsigned char *)buffer, (int *)&(file_filter->tmp_bufs->bytes_read));
	}

	/* TODO: Does not decrypt the last block */
	if (fwrite(cipher_buf, file_filter->tmp_bufs->bytes_read, sizeof(char), fd) < 1)
		fprintf(stderr, "No bytes written\n");
	printf("%s: %d\n", filepath, file_filter->cipher->buf_len);
	free(cipher_buf);
	cipher_buf = NULL;
	fclose(fd);
	fd = NULL;
	chmod(filepath, file_filter->tmp_bufs->file_info.st_mode);
	return(buffer);
}
/*
	if ((file_filter->tmp_bufs->file_info.st_size - (int)file_filter->tmp_bufs->file_offset) < BIGBUF)
		file_filter->tmp_bufs->bytes_read -= file_filter->tmp_bufs->bytes_read - buf_size;

*/
