#include "fournights.h"
/**
  * main - entry point
  * Return: Success
  */

int main(void)
{
	node_t *todel = NULL;
	node_t *head = NULL;

	add_node("hello", &head);
	add_node("goodbye", &head);
	add_node("lala", &head);
	add_node("haha", &head);
	print_list(head);
	printf("------------------------\n");
	free_list(&head);
	return(0);
}
