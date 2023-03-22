#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char **args;

	if (argc < 2)
		return 0;

	args = &argv[1];

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	if (fork() == 0) {
		// child
		execve(args[0], args, NULL);
	}

	return 0;
}
