#include "shell.h"

int main(void) {
    char *command;
    char **args;
    int status;

    do {
        printf("$ ");
        command = read_command();
        args = splitLine(command);
        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                free(command);
                free(args);
                exit(EXIT_SUCCESS);
            }

        status = exe_command(args);
} else {
            status = 1;  
        }
        free(command);
        free(args);
    } while (status);

    return EXIT_SUCCESS;
}
