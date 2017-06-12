#include "fournights.h"

char *encrypt_w_aes(char *buffer, size_t size)
{
	char *tmp;

	if((tmp = malloc(size * sizeof(char *))) == NULL)
		return(NULL);
	if (my_strncat(tmp, buffer, 0, size) == NULL)
		return(NULL);
	printf("%s\n", tmp);
	printf("%d\n", (int)size);
	return(NULL);
}
