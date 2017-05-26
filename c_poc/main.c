#include "fournights.h"

/**
  * regex - search for a substring at the end of a string
  * @str: String to search through
  * @len: Length of the string
  * @list_extensions: ptr to a linked list of file extensions
  * Return: index of substring, -1 if not found
 **/
static int regex(const char *str, size_t len, node_t *list_extensions)
{

	if (!(find_substr_end(read->d_name, ".txt")))
		return (0);
	return (0);
}

/**
  * recurse_ls - Searches through a target directory for all files,
 (* and builds a linked list of those files
  * @dirpath: target directory
  * @head: head of the linked list
  * @list_extensions: ptr to a linked list of file extensions
  * Return: Returns a pointer to the head of the linked list
 **/
node_t *recurse_ls(char *dirpath, node_t **head, node_t *list_extensions)
{
	size_t len_dirpath, len_filename, calloc_size;
	char *filepath;
	DIR *dir;
	struct dirent *read;
	struct stat file_info;

	dir = opendir(dirpath);
	if (!dir)
		return (NULL);
	len_filename = 0;
	len_dirpath = my_strlen(dirpath);
	calloc_size = len_dirpath + BUFSIZE;
	filepath = my_calloc(calloc_size, sizeof(char));
	my_strncat(filepath, dirpath, 0, my_strlen(dirpath));
	while ((read = readdir(dir)))
	{
		if (my_strncmp(read->d_name, ".", 1) != 0 &&
			my_strncmp(read->d_name, "..", 2) != 0)
		{
			len_filename = my_strlen(read->d_name);
			if (regex(read->d_name, len_filename, list_extensions) == 0)
				continue;
			if ((len_filename + len_dirpath + 1) > calloc_size)
			{
				recalloc(filepath, calloc_size, calloc_size + BUFSIZE);
				calloc_size += BUFSIZE;
			}
			my_strncat(filepath, read->d_name, len_dirpath, len_filename);
			lstat(filepath, &file_info);
			if (S_ISDIR(file_info.st_mode) != 0)
			{
				my_strncat(filepath, "/", len_dirpath + len_filename, 1);
				recurse_ls(filepath, head);
			}
			else
				add_node(filepath, head);
		}
	}
	free(filepath);
	closedir(dir);
	return (*head);
}

/**
  * main - Entry point
  * @ac: argument count
  * @av: argument vectors
  * Return: 0
 **/
int main(int ac, char *av[])
{
	char *file_exts = "/home/vagrant/FourNights/c_poc/toEncrypt.txt";
	char *default_dir = "/home/vagrant/FourNights/TESTS/";
	node_t *head_exts = NULL;
	node_t *head_files = NULL;

	head_exts = build_ext_list(file_exts, &head_exts, add_node);
	recurse_ls(ac > 1 ? av[1] : default_dir, &head_files, &head_exts);
	print_list(head_files);
	/* print_list(head_exts); */
	free_list(&head_files);
	free_list(&head_exts);
	return (EXIT_SUCCESS);
}
