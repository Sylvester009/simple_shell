#include "shell.h"

char *read_command(void) {
    char *command = NULL;
    size_t bufsize = 0;

    if (getline(&command, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            fprintf(stderr, "$: Exiting...\n");
            exit(EXIT_SUCCESS);  /* Ctrl-D pressed, exit the shell */
        } else {
            perror("read_command");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}

char **splitLine(char *command) {
    int bufsize = BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        perror("splitLine");
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
                perror("splitLine");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIMETER);
    }
    tokens[position] = NULL;
    return (tokens);
}
