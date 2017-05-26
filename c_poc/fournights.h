#ifndef FOUR_NIGHTS
#define FOUR_NIGHTS

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 1024

/* Linked list functions, etc*/
/*
 * node_s - struct to build a singly linked list
 * @filepath: string that represents the target filepath
 * @next: pointer to the next node
 */
typedef struct node_s{
	char *filepath;
	struct node_s *next;
} node_t;

void print_list(node_t *head);
void free_list(node_t **head);
node_t *add_node(char *str, node_t **head);

/* String Functions */
int my_strncmp(const char *s1, const char *s2, size_t n);
size_t my_strlen(const char *s);
char *my_strncat(char *dest, const char *src, size_t offset, size_t n);
unsigned int find_substr_end(char *string, char *substr);

/* Memory Management */
void *my_memset(void *s, char c, size_t n);
void *my_calloc(size_t nmemb, size_t size);
void *recalloc(void *ptr, size_t old_size, size_t new_size);

/* OS functions */
node_t *recurse_ls(char *filepath, node_t **head, node_t *file_exts);
node_t *build_ext_list(const char *filepath, node_t **head, node_t *(*fxn)(char *, node_t **));
int write_to_file(const char *filepath);

/* TODO if enough time */
/* Recreate: */
void *my_malloc(size_t size);
void my_free(void *ptr);

struct dirent *my_readdir(DIR *dirp);
DIR *my_opendir(const char *name);
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);
char *my_strtok_r(char *str, const char *delim, char **saveptr);


#endif
