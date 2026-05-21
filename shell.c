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
 * get_path_env - gets PATH value from environ manually
 *
 * Return: pointer to PATH value or NULL
 */
char *get_path_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}
	return (NULL);
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
	char *ptr, *start;

	if (strchr(cmd, '/'))
		return (cmd);
	path_env = get_path_env();
	if (!path_env || path_env[0] == '\0')
		return (NULL);
	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);
	start = path_copy;
	while (start)
	{
		ptr = strchr(start, ':');
		if (ptr)
			*ptr = '\0';
		dir = start;
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
		if (ptr)
			start = ptr + 1;
		else
			start = NULL;
	}
	free(path_copy);
	return (NULL);
}

/**
 * handle_builtin - handles built-in commands
 * @args: tokenized arguments
 * @line: the input line to free before exit
 * @last_status: exit status of last command
 *
 * Return: 1 if builtin handled, 0 otherwise
 */
int handle_builtin(char **args, char *line, int last_status)
{
	int i;

	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(last_status);
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
 * @line: the input line for memory cleanup
 * @last_status: exit status of last command
 *
 * Return: exit status of command
 */
int execute(char *cmd, char *prog, int count, char *line, int last_status)
{
	char **args, *trimmed, *path;
	pid_t pid;
	int status = 0;

	trimmed = trim(cmd);
	if (trimmed[0] == '\0')
		return (last_status);
	args = tokenize(trimmed);
	if (!args)
		return (last_status);
	if (handle_builtin(args, line, last_status))
	{
		free(args);
		return (0);
	}
	path = find_in_path(args[0]);
	if (!path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog, count, args[0]);
		free(args);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror(prog);
		if (path != args[0])
			free(path);
		free(args);
		return (1);
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
	waitpid(pid, &status, 0);
	if (path != args[0])
		free(path);
	free(args);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
