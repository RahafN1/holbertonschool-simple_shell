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
 * find_in_path - searches for cmd in PATH directories
 * @cmd: the command name
 *
 * Return: full path string or NULL if not found
 */
char *find_in_path(char *cmd)
{
	char *path_env, *path_copy, *dir, *full;
	struct stat st;
	int len;

	if (strchr(cmd, '/'))
		return (cmd);
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full = malloc(len);
		if (!full)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full, "%s/%s", dir, cmd);
		if (stat(full, &st) == 0)
		{
			free(path_copy);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * handle_builtin - handles built-in commands
 * @args: tokenized arguments
 *
 * Return: 1 if builtin handled, 0 otherwise
 */
int handle_builtin(char **args)
{
	int i;

	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		exit(0);
	}
	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
			printf("%s\n", environ[i]);
		return (1);
	}
	return (0);
}

/**
 * execute - forks and executes a command using execve
 * @cmd: the command to execute
 * @prog: name of the shell program (argv[0])
 * @count: command count for error messages
 */
void execute(char *cmd, char *prog, int count)
{
	char **args, *trimmed, *path;
	pid_t pid;
	int status;

	trimmed = trim(cmd);
	if (trimmed[0] == '\0')
		return;
	args = tokenize(trimmed);
	if (!args)
		return;
	if (handle_builtin(args))
	{
		free(args);
		return;
	}
	path = find_in_path(args[0]);
	if (!path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog, count, args[0]);
		free(args);
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror(prog);
		if (path != args[0])
			free(path);
		free(args);
		return;
	}
	if (pid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", prog, count, args[0]);
			if (path != args[0])
				free(path);
			free(args);
			exit(127);
		}
	}
	wait(&status);
	if (path != args[0])
		free(path);
	free(args);
}
