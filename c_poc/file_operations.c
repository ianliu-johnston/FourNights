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
char *read_file(const char *filepath, ransom_t *ransom, char **(*fxn)(char *, ransom_t *ransom))
{
	int read = 0;
	size_t bytes_read = 0;
	FILE *fp = NULL;
	char *buf = NULL;

	fp = fopen(filepath, "r");
	read = getline(&buf, &bytes_read, fp);
	buf[read] = '\0';
	fxn(buf, ransom);

	fclose(fp);
	/* unlink(filepath); */
	return (buf);
}
