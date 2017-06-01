#include "fournights.h"

/**
  * my_memset - fill memory location with a custom byte
  * @s: memory location to fill
  * @c: character to fill it with
  * @n: amount of bytes to fill with the character
  * Return: void pointer to the memory location
 **/
void *my_memset(void *s, char c, size_t n)
{
	size_t i;
	char *tmp;

	if (!s)
		return (NULL);
	tmp = (char *)s;
	for (i = 0; i <= n; i++)
		tmp[i] = c;
	return ((void *)tmp);
}

/**
  * my_calloc - malloc space, and set the memory to zero
  * @nmemb: amount of units to allocate
  * @size: size of each unit
  * Return: void pointer to the new memory location
 **/
void *my_calloc(size_t nmemb, size_t size)
{
	unsigned char *rtn;

	rtn = (unsigned char *)malloc(nmemb * size);
	if (!rtn)
		return (NULL);
	return (my_memset((void *)rtn, '\0', size));
}

/**
  * recalloc - reallocates a memory block and initializes
  * @ptr: pointer to the original memory block
  * @old_size: old size of memory block
  * @new_size: new size of memory block
  * Return: pointer to reallocated memory block
 **/
void *recalloc(void *ptr, size_t old_size, size_t new_size)
{
	char *tmp;
	size_t i;

	if (ptr != NULL && new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		tmp = my_calloc(new_size, sizeof(char));
		return (tmp);
	}
	if (new_size > old_size)
	{
		tmp = malloc(new_size * sizeof(char));
		for (i = 0; i < old_size; i++)
			tmp[i] = *((char *)ptr + i);
		for (; i < new_size; i++)
			tmp[i] = '\0';
		free(ptr);
		return (tmp);
	}
	return (ptr);
}

