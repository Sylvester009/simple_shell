

#include "shell.h"

extern char **environ;

int execute_command(char **args) {
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
        if (execve(command_path, args, environ) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Forking error */
        perror("shell");
    } else {
        /* Parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    free(command_path);
    return 1;
}

char *find_command_path(const char *command) {
    char *path = getenv("PATH");
    char *token, *temp_path;
    char *command_path = NULL;

    if (path == NULL) {
        fprintf(stderr, "Shell: PATH environment variable not set\n");
        return NULL;
    }

    temp_path = strdup(path);
    if (temp_path == NULL) {
        perror("shell");
        exit(EXIT_FAILURE);
    }

    token = strtok(temp_path, ":");
    while (token != NULL) {
        command_path = malloc(strlen(token) + strlen(command) + 2);
        if (command_path == NULL) {
            perror("shell");
            exit(EXIT_FAILURE);
        }
        sprintf(command_path, "%s/%s", token, command);

        if (access(command_path, F_OK | X_OK) == 0) {
            /* Found the executable in the current path*/
            free(temp_path);
            return command_path;
        }

        free(command_path);
        token = strtok(NULL, ":");
    }

    free(temp_path);
    fprintf(stderr, "Shell: Command not found in PATH: %s\n", command);
    return NULL;
}

char *read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            fprintf(stderr, "Shell: Exiting...\n");
            exit(EXIT_SUCCESS);  /* Ctrl-D pressed, exit the shell */
        } else {
            perror("read_line");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}

char **split_line(char *line) {
    int bufsize = BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        perror("split_line");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                perror("split_line");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
