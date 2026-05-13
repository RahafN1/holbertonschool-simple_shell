#include "shell.h"

/**
 * main - entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (line[0] == '\0')
			continue;

		execute(line, argv[0]);
	}

	free(line);
	return (0);
}
