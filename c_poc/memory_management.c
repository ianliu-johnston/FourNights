#include "fournights.h"

/*
 * my_memset - fill memory location with a custom byte
 * @s: memory location to fill
 * @c: character to fill it with
 * @n: amount of bytes to fill with the character
 * Return: void pointer to the memory location
 */
void *my_memset(void *s, int c, size_t n)
{
	size_t i;
	char *tmp;

	tmp = (char *)s;
	if (!s)
		return(NULL);
	for(i = 0; i <= n; i++)
		tmp[i] = c;
	return(tmp);
}

/*
 * my_calloc - malloc space, and set the memory to zero
 * @nmemb: amount of units to allocate
 * @size: size of each unit
 * Return: void pointer to the new memory location
 */
 void *my_calloc(size_t nmemb, size_t size)
{
    unsigned int i;
    unsigned char *rtn;

    rtn = (unsigned char *)malloc(nmemb * size);
    if (!rtn)
        return(NULL);
    for (i = 0; i < (unsigned int)(nmemb * size); i++)
        rtn[i] = '\0';
    return((void *)rtn);
}
