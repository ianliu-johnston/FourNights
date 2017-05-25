#include "fournights.h"
#include "string.h"
/*
 * read_from_file - reads lines from a file, and executes a function on them. Deletes the file afterwards
 * @filepath: filepath to read
 * @fxn: pointer to function to enact on lines
 * Return: number of bytes read
 */
int read_from_file(const char *filepath, void (*fxn)(char *))
{
	int read = 0;
	size_t bytes_read = 0;
	FILE *fp = NULL;
	char *buf = NULL;

	fp = fopen(filepath, "r");
	while ((read = getline(&buf, &bytes_read, fp)) > 0)
	{
		buf[read - 1] = '\0';
		fxn((char *)buf);
	}
	fclose(fp);
	/*
	unlink(filepath);
	*/
	return(bytes_read);
}

int write_to_file(const char *filepath)
{
	filepath++;
	return(0);
}
