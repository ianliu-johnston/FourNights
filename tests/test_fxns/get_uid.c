#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	uid_t uid;
	uid_t euid;

	uid = getuid();
	euid = geteuid();
	printf("uid = %d, euid = %d\n", (int)uid, (int)euid);
	return (0);
}
