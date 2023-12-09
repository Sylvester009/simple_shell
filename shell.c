#include "shell.h"

extern char **environ;

int exe_command(char **args) {
    pid_t pid;
    int status;

    char *cmd_path = command_path(args[0]);

    if (cmd_path == NULL) {
        fprintf(stderr, "Shell: Command not found: %s\n", args[0]);
        return (1);
    }

    pid = fork();
    if (pid == 0) {
        /* Child process */
        if (execve(cmd_path, args, environ) == -1) {
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

    free(cmd_path);
    return (1);
}

char *command_path(const char *comm) {
    char *path = getenv("PATH");
    char *token, *temp_path;
    char *cmd_path = NULL;

    if (path == NULL) {
        fprintf(stderr, "Shell: PATH environment variable not set\n");
        return NULL;
    }

    temp_path = strdup(path);
    if (temp_path == NULL) {
        perror("error");
        exit(EXIT_FAILURE);
    }

    token = strtok(temp_path, ":");
    while (token != NULL) {
        cmd_path = malloc(strlen(token) + strlen(comm) + 2);
        if (cmd_path == NULL) {
            perror("error");
            exit(EXIT_FAILURE);
        }
        sprintf(cmd_path, "%s/%s", token, comm);

        if (access(cmd_path, F_OK | X_OK) == 0) {
            /* Found the executable in the current path*/
            free(temp_path);
            return (cmd_path);
        }

        free(cmd_path);
        token = strtok(NULL, ":");
    }

    free(temp_path);
    fprintf(stderr, "Shell: Command not found in PATH: %s\n", comm);
    return NULL;
}

char *read_command(void) {
    char *command = NULL;
    size_t bufsize = 0;

    if (getline(&command, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            fprintf(stderr, "Shell: Exiting...\n");
            exit(EXIT_SUCCESS);  /* Ctrl-D pressed, exit the shell */
        } else {
            perror("read_command");
            exit(EXIT_FAILURE);
        }
    }

    return (command);
}

char **splitLine(char *command) {
    int bufsize = BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        perror("splitLine");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIMETER);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                perror("splitLine");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIMETER);
    }
    tokens[position] = NULL;
    return (tokens);
}
