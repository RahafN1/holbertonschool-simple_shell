#include "shell.h"

/**
 * main - entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector
 *
 * Return: last command exit status
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int count = 1;
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
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
		status = execute(line, argv[0], count, line, status);
		count++;
	}
	free(line);
	return (status);
}
