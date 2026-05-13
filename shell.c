#include "shell.h"

/**
 * execute - forks and executes a command using execve
 * @cmd: the command to execute
 * @prog: name of the shell program (argv[0])
 */
void execute(char *cmd, char *prog)
{
	char *args[2];
	pid_t pid;
	int status;

	args[0] = cmd;
	args[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror(prog);
		return;
	}

	if (pid == 0)
	{
		if (execve(cmd, args, environ) == -1)
		{
			fprintf(stderr, "%s: No such file or directory\n", prog);
			exit(1);
		}
	}

	wait(&status);
}
