#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
extern char **environ;
char *trim(char *str);
char **tokenize(char *str);
void execute(char *cmd, char *prog, int count, char *line);
char *find_in_path(char *cmd);
int handle_builtin(char **args, char *line);
#endif /* SHELL_H */
