#include "fournights.h"

/**
  * regex - search for a substring at the end of a string
  * @str: String to search through
  * @len: Length of the string
  * @list_extensions: ptr to a linked list of file extensions
  * Return: index of substring, -1 if not found
 **/
int regex(const char *str, size_t len, node_t *list_extensions)
{
	/* Basic Brute force. Use a search algorithm */
	while (list_extensions)
	{
		if (find_substr_end((char *)str, list_extensions->filepath))
			return (1);
		list_extensions = list_extensions->next;
	}
	len++;
	return (0);
}

/**
  * recurse_ls - Searches through a target directory for all files,
 (* and builds a linked list of those files
  * @rootpath: target directory
  * @head: head of the linked list
  * @list_extensions: ptr to a linked list of file extensions
  * Return: Returns a pointer to the head of the linked list
 **/
node_t *recurse_ls(char *rootpath, node_t **head, node_t *list_extensions)
{
	size_t len_rootpath, len_filename, calloc_size;
	char *filepath;
	DIR *dir;
	struct dirent *read;
	struct stat file_info;

	dir = opendir(rootpath);
	if (!dir)
		return (NULL);
	len_filename = 0;
	len_rootpath = my_strlen(rootpath);
	calloc_size = len_rootpath + BUFSIZE;
	filepath = my_calloc(calloc_size, sizeof(char));
	my_strncat(filepath, rootpath, 0, my_strlen(rootpath));
	while ((read = readdir(dir)))
	{
		if (my_strncmp(read->d_name, ".", 1) == 0 ||
			my_strncmp(read->d_name, "..", 2) == 0)
			continue;
		len_filename = my_strlen(read->d_name);
		if ((len_filename + len_rootpath + 1) > calloc_size)
		{
			recalloc(filepath, calloc_size, calloc_size + BUFSIZE);
			calloc_size += BUFSIZE;
		}
		my_strncat(filepath, read->d_name, len_rootpath, len_filename);
		lstat(filepath, &file_info);
		if (S_ISDIR(file_info.st_mode) != 0)
		{
			my_strncat(filepath, "/", len_rootpath + len_filename, 1);
			recurse_ls(filepath, head, list_extensions);
		}
		else if (regex(read->d_name, len_filename, list_extensions) != 0)
			add_node(filepath, head);
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
	char *file_exts = "/home/vagrant/FourNights/c_poc/file_exts.txt";
	char *default_dir = "/home/vagrant/FourNights/TESTS/";
	node_t *head_exts = NULL;
	node_t *head_files = NULL;

	head_exts = build_ext_list(file_exts, &head_exts, add_node);
	recurse_ls(ac == 2 ? av[1] : default_dir, &head_files, head_exts);
	print_list(head_files);
	/*
	print_list(head_exts);
	*/
	free_list(&head_files);
	free_list(&head_exts);
	return (EXIT_SUCCESS);
}
/*
 printf("2 DEBUG");
 getchar();
*/
