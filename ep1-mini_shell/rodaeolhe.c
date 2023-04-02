#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFLEN 1024

/* ideally we'd check for the size of the int, but this is a
 * simple example, so we'll just assume it fits in our buffer */
char* _utoa(int n, char *s)
{
	int i = 0;

	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	s[i] = '\0';

	for (int j = 0; j < i / 2; j++) {
		char tmp = s[j];
		s[j] = s[i - j - 1];
		s[i - j - 1] = tmp;
	}

	return s;
}

int main(int argc, char *argv[])
{
	int statloc = 0;
	char **args;

	/* read command */
	if (argc < 2)
		return 0;

	args = &argv[1];

	if (fork() != 0) {
		// parent
		char status[4]; /* as statloc uses only half the bits (8) to
				   store retvals, we can get 0-255, which should
				   take (at most) 4 bytes to represent */

		if (waitpid(-1, &statloc, 0) < 0)
			exit(errno);

		if (WIFSIGNALED(statloc))
			return WTERMSIG(statloc);

		_utoa(WEXITSTATUS(statloc), status);

		write(STDOUT_FILENO, "=> programa '", 13);
		write(STDOUT_FILENO, args[0], strlen(args[0]));
		write(STDOUT_FILENO, "' retornou com codigo ", 23);
		write(STDOUT_FILENO, status, strlen(status));
		write(STDOUT_FILENO, "\n", 1);
	} else {
		// child
		if (execve(args[0], args, NULL) < 0)
			return -1;
	}

	return statloc;
}
