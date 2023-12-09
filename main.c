#include "shell.h"

int main(void) {
    char *command;
    char **args;
    int status;

    do {
        printf("$ ");
        command = read_command();
        args = splitLine(command);
        status = exe_command(args);

        free(command);
        free(args);
    } while (status);

    return EXIT_SUCCESS;
}
