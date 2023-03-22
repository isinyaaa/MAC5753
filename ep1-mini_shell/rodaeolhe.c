#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFLEN 1024

void _utoa(int n, char *s)
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
		int ret;
		char output[BUFLEN + 1] = "=> programa '",
		     status[4]; /* as statloc uses only half the bits (8) to
				   store retvals, we can get 0-255, which should
				   take (at most) 4 bytes to represent */

		ret = waitpid(-1, &statloc, 0);
		if (ret < 0)
			return ret;

		_utoa(WEXITSTATUS(statloc), status);

		strncat(output, args[0], BUFLEN - strlen(output));
		strncat(output, "' retornou com codigo ", BUFLEN - strlen(output));
		strncat(output, status, BUFLEN - strlen(output));
		strncat(output, "\n", BUFLEN - strlen(output));

		ret = write(STDOUT_FILENO, output, strlen(output));
		if (ret < 0)
			return ret;
	} else {
		// child
		if (execve(args[0], args, NULL) < 0)
			return -1;
	}

	return statloc;
}
