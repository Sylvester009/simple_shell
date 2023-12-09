#include "shell.h"

extern char **environ;

/* Function to execute a command */
int exe_command(char **args) {
    pid_t pid;
    int status;

    char *command_path = find_command_path(args[0]);

    if (command_path == NULL) {
        fprintf(stderr, "Shell: Command not found: %s\n", args[0]);
        return 1;
    }


    pid = fork();
    if (pid == 0) {
        /* Child process */
        if (execve(args[0], args, environ) == -1) {
            perror("error");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Forking error */
        perror("error");
    } else {
        /* Parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return (1);
}

/* Function to read a line from the console */
char *read_command(void) {
    char *command = NULL;
    size_t bufsize = 0;

    if (getline(&command, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);  /* Ctrl-D pressed, exit the shell */
        } else {
            perror("read_command");
            exit(EXIT_FAILURE);
        }
    }

    return command;
}

/* Function to split a line into tokens */
char **splitLine(char *command) {
    int bufsize = BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        perror("splitLine error");
        exit(EXIT_FAILURE);
    }

    token = strtok(command, DELIMETER);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                perror("splitLine error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIMETER);
    }
    tokens[position] = NULL;
    return tokens;
}
