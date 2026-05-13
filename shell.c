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
 * tokenize - splits a string into array of tokens
 * @str: the string to split
 *
 * Return: array of strings or NULL on failure
 */
char **tokenize(char *str)
{
	char **args;
	char *token;
	int i = 0;

	args = malloc(sizeof(char *) * 64);
	if (!args)
		return (NULL);

	token = strtok(str, " \t");
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;
	return (args);
}

/**
 * execute - forks and executes a command using execve
 * @cmd: the command to execute
 * @prog: name of the shell program (argv[0])
 */
void execute(char *cmd, char *prog)
{
	char **args;
	char *trimmed;
	pid_t pid;
	int status;

	trimmed = trim(cmd);

	if (trimmed[0] == '\0')
		return;

	args = tokenize(trimmed);
	if (!args)
		return;

	pid = fork();
	if (pid == -1)
	{
		perror(prog);
		free(args);
		return;
	}

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "%s: No such file or directory\n", prog);
			free(args);
			exit(1);
		}
	}

	wait(&status);
	free(args);
}
