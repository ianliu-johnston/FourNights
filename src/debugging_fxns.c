#include "fournights.h"
/**
  * debug_list - prints elements of the tmp_bufs struct
  * @tmp_bufs: lala
  */
void debug_list(tmp_bufs_t *tmp_bufs)
{
	printf("--------%s--------\n", tmp_bufs->filepath);
	printf("bytes_read: %d\n", (int)tmp_bufs->bytes_read);
	printf("file_offset: %d\n", (int)tmp_bufs->file_offset);
	printf("st_size: %d\n", (int)tmp_bufs->file_info.st_size);
	tmp_bufs->plaintext[400] = '\0';
	printf("%s...(truncated)...", tmp_bufs->plaintext);
	getchar();
}
/**
  * print_for_debug - prints elements of the struct for debugging
  * @file_filter: pointer to the file_filter struct
  */
void print_for_debug(struct file_filter_s file_filter)
{
	int debug_int = 0;
	char **debug_dp = NULL;

	/* PRINT STRUCT FOR DEBUGGING */
	printf("DEBUG 0: root_path: %s\n", file_filter.root_path);
	printf("DEBUG 2: file extension list \n");
	debug_dp = file_filter.file_extensions;
	for (debug_int = 0; debug_dp[debug_int] != NULL; debug_int++)
		printf("%s%s", debug_int == 0 ? "" : ", ", debug_dp[debug_int]);
	getchar();
	printf("\nHas NULL at end? %s\n", debug_dp[debug_int]);
	getchar();
}
