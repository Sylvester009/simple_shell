#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 *struct map - a struct that maps a command name to a function 
 *
 *@command_name: name of the command
 *@func: the function that executes the command
 */

typedef struct map
{
	char *command_name;
	void (*func)(char **command);
} function_map;

extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

void prompt_print(const char *string, int fd);
void remove_newline(char *str);
void remove_comment(char *input);
char *_strtok(char *str, const char *delim, char **save_ptr);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
char **tokenize(char *input_string, const char *delim);
void non_interact(void);
void handle_interrupt(int signo);
int parse_command(char *cmd);
void initialize_command(char **args, int cmd_type);

#endif
