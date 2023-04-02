#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 1
#define BUFLEN 1024
#define MAXARGS 128

void handle_sig(int sig)
{
	exit(128 + sig);
}

int main()
{
	char buf[BUFLEN + 1];
	buf[BUFLEN] = '\0';

	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);

	while (TRUE) {
		int argc = 0, statloc = 0;
		char *delim, *last, *args[MAXARGS + 1];
		ssize_t n;

		/* print prompt */
		write(STDOUT_FILENO, "> ", 2);

		/* read command */
		n = read(STDIN_FILENO, buf, BUFLEN - 1);
		if (n < 0)
			exit(errno);

		/* EOF */
		if (n == 0)
			exit(0);

		/* remove newline */
		buf[n - 1] = '\0';

		delim = strtok_r(buf, " ", &last);
		while (delim != NULL && argc < MAXARGS) {
			args[argc] = delim;
			argc++;
			delim = strtok_r(NULL, " ", &last);
		}
		args[argc] = NULL;

		if (fork() != 0) {
			// parent
			if (waitpid(-1, &statloc, 0) < 0)
				exit(errno);
		} else {
			// child
			if (execvp(args[0], args) < 0)
				exit(errno);
		}
	}

	return 0;
}
