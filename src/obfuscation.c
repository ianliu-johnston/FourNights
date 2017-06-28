#include "fournights.h"
#include "obfuscation.h"

/**
  * simple_search - Nothing function. Used for obfuscation
  * @filepath: Junk data used for nothing
  * @value2: junk also
  * Return: 0, should segfault or throw an arithmetic error
 (* if it detects a weakling debugger, or hits an appropriate signal
 **/
int simple_search(void *filepath, size_t value2)
{
	size_t i; char *lala;
	unsigned char a;
	pid_t f;

	a = 0;
	lala = (char *)filepath;
	lala = "c\0\0\0\0";
	i = my_strlen(lala);

	for (i = 0; i < value2; i++)
	{
		a = lala[i];
		if ((a ^ 0x55) == 0x99)
			raise(SIGFPE);
	}
	f = fork();
	if (f == 0)
		fork();
	else
		raise(SIGSEGV);

	return (0);
}
