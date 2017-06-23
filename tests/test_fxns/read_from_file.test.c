#include "fournights.h"

int main(void)
{
	int status = 0;
	char *filepath = "/home/vagrant/FourNights/c_poc/toEncrypt.txt";
	status = read_from_file(filepath, puts);
	printf("Bytes Read: %d\n", status);
	lstat(filepath, F_OK);
	return(EXIT_SUCCESS);
}
