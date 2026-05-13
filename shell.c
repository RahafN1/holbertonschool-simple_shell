#include "shell.h"

/**
 * trim - removes leading and trailing spaces from a string
 * @str: the string to trim
 *
 * Return: pointer to trimmed string
 */
char *trim(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t')
		str++;

	if (*str == '\0')
		return (str);

	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
		end--;

	*(end + 1) = '\0';
	return (str);
}

/**
 * execute - forks and executes a command using execve
 * @cmd: the command to execute
 * @prog: name of the shell program (argv[0])
 */
void execute(char *cmd, char *prog)
{
	char *args[2];
	char *trimmed;
	pid_t pid;
	int status;

	trimmed = trim(cmd);

	if (trimmed[0] == '\0')
		return;

	args[0] = trimmed;
	args[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror(prog);
		return;
	}

	if (pid == 0)
	{
		if (execve(trimmed, args, environ) == -1)
		{
			fprintf(stderr, "%s: No such file or directory\n", prog);
			exit(1);
		}
	}

	wait(&status);
}
