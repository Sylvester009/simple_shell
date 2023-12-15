#include "shell.h"

char **command = NULL;
char *input_line = NULL;
char *shell_alias = NULL;
int status = 0;

/**
 * main - entry point for the shell program
 * @argc: number of arguments
 * @argv: program arguments
 *
 * Implements a simple shell with basic commands.
 * Handles signals, parses input, and executes commands.
 * Returns: 0 on success
 */

int main(int argc __attribute__((unused)), char **argv) {
    char **current_args = NULL;
    int i, command_type = 0;
    size_t buffer_size = 0;

    signal(SIGINT, handle_interrupt);
    shell_alias = argv[0];

    while (1) {
        non_interactive();
        print_prompt("$ ", STDOUT_FILENO);

        if (getline(&input_line, &buffer_size, stdin) == -1) {
            free(input_line);
            exit(status);
        }

        remove_newline(input_line);
        remove_comment(input_line);
        command = tokenizer(input_line, ";");

        for (i = 0; command[i] != NULL; i++) {
            current_args = tokenizer(command[i], " ");
            if (current_args[0] == NULL) {
                free(current_args);
                break;
            }
            command_type = parse_command(current_args[0]);

            /* initialize command */
            initialize_command(current_args, command_type);
            free(current_args);
        }
        free(command);
    }

    free(input_line);
    return (status);
}


/**
 * print_prompt - prints the shell prompt
 * @prompt: the prompt string to be printed
 * @fd: file descriptor to print to
 */
void print_prompt(const char *prompt, int fd) {
    size_t len = 0;

    while (string[len] != '\0') {
        len++;
    }

    write(fd, string, len);
}
