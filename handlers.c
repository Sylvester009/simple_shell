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
