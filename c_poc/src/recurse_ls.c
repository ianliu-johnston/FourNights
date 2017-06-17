#include "fournights.h"
/**
  * recurse_ls - Searches through a target directory for all files,
 (* and builds a linked list of those files
  * @rootpath: target directory
  * @head: head of the linked list
  * @list_extensions: ptr to a linked list of file extensions
  * Return: Returns a pointer to the head of the linked list
 **/
void *recurse_ls(char *dirname, file_filter_t *file_filter)
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
		printf("Is %s a directory? %d\n", read->d_name, binary_search_string(read->d_name, len_filename, file_filter));
		getchar();
#endif
		if (S_ISDIR(file_info.st_mode) != 0)
		{
			my_strncat(filepath, "/", len_rootpath + len_filename, 1);
			recurse_ls(filepath, file_filter);
		}
		else if ((binary_search_string(read->d_name, len_filename, file_filter) != 0) && S_ISREG(file_info.st_mode) != 0)
		{
			file_filter->tmp_bufs->file_info = file_info;
			my_strncat(file_filter->tmp_bufs->filepath, filepath, 0, my_strlen(filepath));
			do
			{
				file_filter->tmp_bufs->bytes_read = read_file(file_filter->tmp_bufs->filepath, file_filter, write_file);
#ifndef NO_DEBUG
				debug_list(file_filter->tmp_bufs);
#endif
			}
			while(file_filter->tmp_bufs->file_offset < file_filter->tmp_bufs->file_info.st_size);
			/* reset bytes read and file_offset.  */
			file_filter->tmp_bufs->file_offset = 0;
			file_filter->tmp_bufs->bytes_read = 0;
			/* Disabled for debugging. Will remove reference to original file
			*/
			unlink(filepath);
		}
	}
	free(filepath);
	closedir(dir);
	return (file_filter);
}
