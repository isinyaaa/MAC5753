#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define ONLYME 0700

int main(int argc, char *argv[])
{
	char *filename;
	struct stat filestat;

	if (argc != 2)
		return 1;

	filename = argv[1];

	if (stat(filename, &filestat) == -1)
		exit(errno);

	return chmod(filename, ONLYME);
}
