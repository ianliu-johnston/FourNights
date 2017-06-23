#include <stdio.h>
/*
 * super quick test for the bash command:
 * for i in {1..20}; do $(./a.out $i > $i.txt); done
 * for i in {1..20}; do cat -e $i; done
 * compile with gcc
 */

int main(int ac, char *av[])
{
	int i;

	for (i = 0; i < atoi(av[1]); i++)
		putchar(i + 'a');
	putchar('\n');
	return(0);
}
