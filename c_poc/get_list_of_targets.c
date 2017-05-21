#include "fournights.h"

int main(void)
{
	int count;
	DIR *dir;
	struct stat *buf;
	struct dirent *read;
	node_t *head;

	head = NULL;
	dir = opendir("TESTS");
	while(read = readdir(dir))
	{
		add_node(read->d_name, &head);
		count = lstat(read->d_name, buf);
		printf("%d\n", count);
	}
	closedir(dir);
	print_list(head);
	free_list(&head);
	return(0);
}
