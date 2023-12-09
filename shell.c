#include "shell.h"

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
