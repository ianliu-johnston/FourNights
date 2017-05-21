#include "fournights.h"

/*
 * add_node - Add a node to the beginning of a list
 * @str: string to put into each node
 * @head: head of the linked list
 * Return: newly created node
 */
node_t *add_node(const char *str, node_t **head)
{
	node_t *new_node, *temp;

	if (!str)
		return(NULL);
	new_node = malloc(sizeof(node_t));
	if(!new_node)
		return(NULL);
	new_node->filepath = (char *)str;
	new_node->next = *head;

	*head = new_node;
	return(new_node);
}

/*
 * free_list - Frees a linked list
 * @head: head of the linked list
 */
void free_list(node_t **head)
{
	node_t *temp;

	while(*head)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
		temp = NULL;
	}
}

/*
 * print_list - prints the strings in a linked list
 * @head: head of the linked list
 */
void print_list(node_t *head){
	while(head)
	{
		printf("%s\n", head->filepath);
		head = head->next;
	}
}
