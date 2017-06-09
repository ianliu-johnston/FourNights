#include "fournights.h"
#include "obfuscation.h"

int simple_search(void *filepath, size_t value2)
{
	size_t i; char *lala;
	unsigned char a;

	a = 0;
	lala = (char *)filepath;
	i = my_strlen(lala);

	for (i = 0; i < value2; i++)
	{
		a = lala[i];
		if ((a ^ 0x55) == 0x99)
			return (1);
	}

	return (0);
}
