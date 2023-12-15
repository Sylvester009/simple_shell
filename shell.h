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

#define COMMAND_EXTERNAL 1
#define COMMAND_INTERNAL 2
#define COMMAND_PATH 3
#define COMMAND_INVALID -1

#define STDOUT_FILENO 1
#define F_OK 0

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

void print_prompt(const char *string, int fd);
void remove_newline(char *str);
void remove_comment(char *input);
char *_strtok(char *str, const char *delim, char **save_ptr);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
char **tokenize(char *input_string, const char *delim);
void non_interact(void);
void handle_interrupt(int signo);
void initialize_command(char **args, int cmd_type);

int _strspn(char *str, char *accept);
int _strcspn(char *str, char *reject);
char *_strchr(char *s, char c);

int classify_command(char *cmd);
char *command_path(char *cmd);
char *_getenv;

#endif
