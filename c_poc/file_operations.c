#include "fournights.h"
#include "string.h"
/**
  * build_ext_list - reads lines from a file, and executes a function on them.
  * Deletes the file afterwards
  * @filepath: filepath to read
  * @head: head of a linked list
  * @fxn: pointer to function to enact on lines
  * Return: number of bytes read
 **/
node_t *build_ext_list(
		const char *filepath,
		node_t **head,
		node_t *(*fxn)(char *, node_t **))
{
	int read = 0;
	size_t bytes_read = 0;
	FILE *fp = NULL;
	char *buf = NULL;

	fp = fopen(filepath, "r");
	while ((read = getline(&buf, &bytes_read, fp)) > 0)
	{
		buf[read - 1] = '\0';
		fxn(buf, head);
	}
	free(buf);
	fclose(fp);
	/* unlink(filepath); */
	return (*head);
}
