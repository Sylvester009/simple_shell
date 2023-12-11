#include "shell.h"

int my_atoi(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    /* Handle whitespaces*/
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
        i++;
    }

    /* Handle signs */
    if (str[i] == '-' || str[i] == '+') {
        sign = (str[i++] == '-') ? -1 : 1;
    }

    /* Converts digits to integer*/
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i++] - '0');
    }

    return sign * result;
}

void exit_shell(char **args) {
    if (args[1] != NULL) {
        int status = my_atoi(args[1]);
        printf("Shell: Exiting with status %d...\n", status);
        exit(status);
    } else {
        printf("Shell: Exiting...\n");
        exit(EXIT_SUCCESS);
    }
}

void set_env_var(char **args) {
    if (args[1] != NULL && args[2] != NULL && args[3] == NULL) {
        if (setenv(args[1], args[2], 1) != 0) {
            fprintf(stderr, "Shell: Failed to set environment variable %s\n", args[1]);
        }
    } else {
        fprintf(stderr, "Shell: Usage: setenv VARIABLE VALUE\n");
    }
}

void unset_env_var(char **args) {
    if (args[1] != NULL && args[2] == NULL) {
        if (unsetenv(args[1]) != 0) {
            fprintf(stderr, "Shell: Failed to unset environment variable %s\n", args[1]);
        }
    } else {
        fprintf(stderr, "Shell: Usage: unsetenv VARIABLE\n");
    }
}

