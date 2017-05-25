#include "fournights.h"

/*
 * recurse_ls - Searches through a target directory for all files, and builds a linked list
 * @dirpath: target directory
 * @head: head of the linked list
 * Return: Returns a pointer to the head of the linked list
 */
node_t *recurse_ls(char *dirpath, node_t **head)
{
	char *filepath;
	DIR *dir;
	struct dirent *read;
	struct stat file_info;

	dir = opendir(dirpath);
	if (!dir)
		return(NULL);
	while((read = readdir(dir)))
	{
		/* Eliminate directories: "." and ".." */
		if (my_strncmp(read->d_name, ".", 1) != 0 &&
			my_strncmp(read->d_name, "..", 2) != 0)
		{
			if (!(find_substr_end(read->d_name, ".txt")))
				continue;
			/* build filepath */
			filepath = my_calloc((my_strlen(dirpath) + my_strlen(read->d_name) + 2) * sizeof(char), sizeof(char));
			my_strncat(filepath, dirpath, my_strlen(dirpath));
			my_strncat(filepath, read->d_name, my_strlen(read->d_name));
			lstat(filepath, &file_info);
			if (S_ISDIR(file_info.st_mode) != 0)
			{
				my_strncat(filepath, "/", 1);
				recurse_ls(filepath, head);
				free(filepath);
			}
			else
				add_node(filepath, head);
		}
	}
	closedir(dir);
	return(*head);
}
