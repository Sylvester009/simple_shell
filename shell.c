#include "shell.h"

char *read_command(void) {
    char *command = NULL;
    size_t bufsize = 0;
    ssize_t read_input;

    read_input = getline(&command, &bufsize, stdin);

    if (read_input == -1) {
        if (feof(stdin)) {
            fprintf(stderr, "$: Exiting...\n");
            exit(EXIT_SUCCESS);  /* Ctrl-D pressed, exit the shell */
        } else {
            perror("read_command");
            exit(EXIT_FAILURE);
        }
    }

    return (command);
}

char *_strtok(char *str, const char *delim) {
    static char *last_token = NULL;
    char *token_end;

    /* If string is not provided, continue with the last token*/
    if (str == NULL && last_token != NULL) {
        str = last_token;
    }

    str += strspn(str, delim);

    /* If the string is empty */
    if (*str == '\0') {
        last_token = NULL;
        return NULL;
    }

    /* Find the end of the token */
    token_end = str + strcspn(str, delim);

    
    if (*token_end != '\0') {
        *token_end = '\0';
        last_token = token_end + 1;
    } else {
        
        last_token = NULL;
    }

    return str;
}

char **splitLine(char *command) {
    int bufsize = BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        perror("splitLine");
        exit(EXIT_FAILURE);
    }

    token = _strtok(command, DELIMETER);
    while (token != NULL) {
        tokens[position] = strdup(token);
        position++;

        if (position >= bufsize) {
            bufsize += BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                perror("splitLine");
                exit(EXIT_FAILURE);
            }
        }

        token = _strtok(NULL, DELIMETER);
    }
    tokens[position] = NULL;
    return (tokens);
}
