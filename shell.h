#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFSIZE 1024
#define DELIMETER " \t\r\n\a"

/* Function prototypes */
int exe_command(char **args);
char *read_command(void);
char **splitLine(char *command);
char *command_path(const char *comm);

int my_atoi(const char *str);
void exit_shell(char **args);
void set_env_var(char **args);
void unset_env_var(char **args);


#endif /* SHELL_H */
