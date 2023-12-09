

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFSIZE 1024
#define DELIM " \t\r\n\a"

/* Function prototypes */
int execute_command(char **args);
char *read_line(void);
char **split_line(char *line);
char *find_command_path(const char *command);

#endif /* SHELL_H */
