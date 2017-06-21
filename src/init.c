#include "fournights.h"

/**
  * init_struct - Initializes the main struct and its nested struct
  * @file_filter: Main struct
  * @target_dir: directory to encrypt
  * Return: pointer to the initialized structure, NULL on error
 **/
file_filter_t *init_struct(file_filter_t *file_filter, char *target_dir)
{
	char file_exts[1024];

	if (!file_filter || !target_dir ||
		!(file_filter->tmp_bufs = malloc(sizeof(tmp_bufs_t))) ||
		!(file_filter->tmp_bufs->filepath = my_calloc(PATH_MAX, sizeof(char))) ||
		!(file_filter->tmp_bufs->plaintext = my_calloc(BIGBUF * sizeof(char), sizeof(char))))
		return (NULL);
	file_filter->tmp_bufs->file_offset = 0;
	file_filter->tmp_bufs->bytes_read = 0;
	/* Ho!! Look a hardcoded key?! */
	file_filter->key = "9cd28b6451a8000a9092ab62aea609ee";
	file_filter->cipher_flag = 'e'; /* set cipher_flag to encrypt */
	file_filter->root_path = target_dir;
	if (!(getcwd(file_exts, sizeof(file_exts))) ||
		!(my_strncat(file_exts, "/file_exts.txt\0", my_strlen(file_exts), 15)))
			return(NULL);
	lstat(file_exts, &(file_filter->tmp_bufs->file_info));
	if(read_file(file_exts, file_filter, tokenizer) < 1)
	{
		fprintf(stderr, "No Bytes read\n");
		return(NULL);
	}
	/* reset file_offset and bytes_read */
	file_filter->tmp_bufs->file_offset = 0;
	file_filter->tmp_bufs->bytes_read = 0;
	return(file_filter);
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
