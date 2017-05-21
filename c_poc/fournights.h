#ifndef FOUR_NIGHTS
#define FOUR_NIGHTS

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>


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
node_t *add_node(const char *str, node_t **head);


#endif
