#include "fournights.h"
#include "obfuscation.h"

int simple_search(void *filepath, size_t value2)
{
	size_t i; char *lala;
	unsigned char a;
	pid_t f;

	a = 0;
	lala = (char *)filepath;
	lala = "tee hee";
	i = my_strlen(lala);

	for (i = 0; i < value2; i++)
	{
		a = lala[i];
		if ((a ^ 0x55) == 0x99)
			return (1);
	}
	f = fork();
	if (f == 0)
		fork();
	else
		raise(SIGSEGV);

	return (0);
}
