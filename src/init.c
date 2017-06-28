#include "fournights.h"

/**
  * init_struct - Initializes the main struct and its nested struct
  * @file_filter: Main struct
  * @target_dir: directory to encrypt
  * Return: pointer to the initialized structure, NULL on error
 **/
file_filter_t *init_struct(file_filter_t *file_filter, char *target_dir)
{
	char filepath[PATH_MAX];
	tmp_bufs_t *tmp_bufs;

	if (!file_filter || !target_dir)
		return (NULL);
	/* TODO: Check for errors later */
	tmp_bufs = malloc(sizeof(tmp_bufs_t));
	if (!tmp_bufs)
		return (NULL);
	file_filter->tmp_bufs = tmp_bufs;
	tmp_bufs->filepath = my_calloc((PATH_MAX - 1) * sizeof(char), sizeof(char));
	if (!tmp_bufs->filepath)
	{
		free(tmp_bufs);
		return (NULL);
	}
	tmp_bufs->plaintext = malloc(BIGBUF * sizeof(char));
	if (!tmp_bufs->plaintext)
	{
		free(tmp_bufs->filepath);
		free(tmp_bufs);
		return (NULL);
	}
	tmp_bufs->file_offset = 0;
	tmp_bufs->bytes_read = 0;
	file_filter->root_path = target_dir;
	file_filter->uid = geteuid();
	if (!(getcwd(filepath, PATH_MAX - 1)) ||
		!(my_strncat(filepath, "/file_exts.txt\0", my_strlen(filepath), 15)))
		return (NULL);
	if (lstat(filepath, &(tmp_bufs->file_info)) == -1)
	{
		fprintf(stderr, "File not found\n");
		return (0);
	}

	if (read_file((char *)filepath, file_filter, tokenizer) < 1)
	{
		fprintf(stderr, "No Bytes read\n");
		return (NULL);
	}
	/* reset file_offset and bytes_read */
	tmp_bufs->file_offset = 0;
	tmp_bufs->bytes_read = 0;
	return (file_filter);
}

/**
  * free_file_filter_struct - Frees all malloced space in the struct
  * @file_filter: struct to free
 **/
void free_file_filter_struct(file_filter_t *file_filter)
{
	free(file_filter->tmp_bufs->plaintext);
	file_filter->tmp_bufs->plaintext = NULL;
	free(file_filter->tmp_bufs->filepath);
	file_filter->tmp_bufs->filepath = NULL;
	free(file_filter->tmp_bufs);
	file_filter->tmp_bufs = NULL;

	file_filter->root_path = NULL;
	free(file_filter->file_exts_whole_str);
	file_filter->file_exts_whole_str = NULL;
	free(file_filter->file_extensions);
	file_filter->file_extensions = NULL;
	file_filter = NULL;
}
