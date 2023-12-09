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
#define DELIMETER " \t\r\n\a"

extern char **environ;

/* Function prototypes */
int exe_command(char **args);
char *read_command(void);
char **splitLine(char *command);
void exe_command_i(void);
void exe_command_nil(char *filename);

char *find_command_path(const char *command);

#endif /* SHELL_H */
