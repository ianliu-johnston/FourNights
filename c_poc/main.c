#include "fournights.h"

int main(int ac, char *av[])
{
	int status;
	char *default_dir = "/home/vagrant/FourNights/TESTS/";
	char *file_exts = "/home/vagrant/FourNights/c_poc/toEncrypt.txt";
	node_t *head_files = NULL;
	node_t *head_exts = NULL;

	/* Build a linked list of files in the target directory. In this case, default_dir */
	recurse_ls(ac > 1 ? av[1] : default_dir, &head_files);
	status = read_from_file(file_exts, add_node);

	print_list(head_files);
	print_list(head_exts);
	printf("%d\n", status);

	free_list(&head_files);
	free_list(&head_exts);
	return(0);
}
