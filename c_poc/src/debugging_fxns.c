#include "fournights.h"
/**
  * debug_list - prints elements of the target_file_buf struct
  * @target_file_buf: lala
  */
#ifndef NO_DEBUG
#define NO_DEBUG
void debug_list(target_file_t *target_file_buf)
{
	printf("--------%s--------\n", target_file_buf->filepath);
	printf("bytes_read: %d\n", (int)target_file_buf->bytes_read);
	printf("file_offset: %d\n", (int)target_file_buf->file_offset);
	printf("st_size: %d\n", (int)target_file_buf->file_info.st_size);
	target_file_buf->buf[400] = '\0';
	printf("%s...(truncated)...", target_file_buf->buf);
	getchar();
}
/**
  * print_for_debug - prints elements of the struct for debugging
  * @ransom: pointer to the ransom struct
  */
void print_for_debug(struct ransom_s ransom)
{
	int debug_int = 0;
	char **debug_dp = NULL;

	/* PRINT STRUCT FOR DEBUGGING */
	printf("DEBUG 0: root_path: %s\n", ransom.root_path);
	printf("DEBUG 1: os_info.sysname: %s, .nodename: %s, .release: %s, .version: %s, .machine: %s\n", ransom.os_info.sysname, ransom.os_info.nodename, ransom.os_info.release, ransom.os_info.version, ransom.os_info.machine);

	printf("DEBUG 2: file extension list \n");
	debug_dp = ransom.file_extensions;
	for (debug_int = 0; debug_dp[debug_int] != NULL; debug_int++)
		printf("%s%s", debug_int == 0 ? "" : ", ", debug_dp[debug_int]);
	getchar();
	printf("\nHas NULL at end? %s\n", debug_dp[debug_int]);
	printf("Filebuffer: Still alive? (strtok truncates past first file ext) %s\n", ransom.file_ext_nontoken);
	getchar();
	printf("Number of extensions to search: %d\n", ransom.num_of_file_ext);
	printf("DEBUG 3: \n");
	print_list(ransom.target_files);
}
/**
  * print_list - prints the strings in a linked list
  * @head: head of the linked list
  * For DEBUGGING
 **/
void print_list(node_t *head)
{
	if (!head)
		printf("Nothing to print\n");
	while (head)
	{
		printf("%s\n", head->str);
		head = head->next;
	}
}
#endif
