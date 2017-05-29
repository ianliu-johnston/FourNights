#include "fournights.h"

/**
  * add_node - Add a node to the beginning of a list
  * @str: string to put into each node
  * @head: head of the linked list
  * Return: newly created node
 **/
node_t *add_node(char *str, struct node_s **head)
{
	char *str_cpy;
	node_t *new_node;

	if (!str)
		return (NULL);
	new_node = malloc(sizeof(node_t));
	if (!new_node)
		return (NULL);
	str_cpy = my_calloc((my_strlen(str) + 1) * sizeof(char), sizeof(char));
	if (!str_cpy)
	{
		free(new_node);
		return (NULL);
	}
	new_node->str = my_strncat(str_cpy, str, 0, my_strlen(str) + 1);
	if (!(new_node->str))
	{
		free(new_node);
		free(str_cpy);
		return (NULL);
	}
	new_node->next = *head;

	*head = new_node;
	return (new_node);
}


/**
  * free_list - Frees a linked list
  * @head: head of the linked list
 **/
void free_list(node_t **head)
{
	node_t *temp;

	if (!(*head))
		return;
	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->str);
		temp->str = NULL;
		free(temp);
		temp = NULL;
	}
	free(*head);
	*head = NULL;
	head = NULL;
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

