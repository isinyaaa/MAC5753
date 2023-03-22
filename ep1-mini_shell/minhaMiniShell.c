#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 1
#define BUFLEN 1024

void handle_sig(int sig)
{
	exit(0);
}

int main()
{
	int ret = 0;
	char buf[BUFLEN + 1];
	buf[BUFLEN] = '\0';

	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);

	while (TRUE) {
		int argc = 0, statloc = 0;
		char *delim, *last, *args[BUFLEN];

		/* print prompt */
		ret = write(STDOUT_FILENO, "> ", 2);
		if (ret < 0)
			return ret;

		/* read command */
		ret = read(STDIN_FILENO, buf, BUFLEN - 1);
		if (ret <= 0)
			return ret;

		/* remove newline */
		buf[ret - 1] = '\0';

		delim = strtok_r(buf, " ", &last);
		while (delim != NULL) {
			args[argc] = delim;
			argc++;
			delim = strtok_r(NULL, " ", &last);
		}
		args[argc] = NULL;

		if (fork() != 0) {
			// parent
			ret = waitpid(-1, &statloc, 0);
			if (ret < 0)
				return ret;
		} else {
			// child
			if (execvp(args[0], args) < 0)
				return -1;
		}
	}

	return ret;
}
