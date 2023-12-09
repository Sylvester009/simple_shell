#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define BUFSIZE 1024
#define DELIM " \t\r\n\a"

extern char **environ;

/* Function prototypes */
int execute_command(char **args);
char *read_line(void);
char **split_line(char *line);

#endif /* SHELL_H */
