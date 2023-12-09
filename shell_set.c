#include "shell.h"

void exe_command_i(void) {
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
            status = 1;  /** Empty command, continue the loop*/
        }

        free(command);
        free(args);
    } while (status);
}

void exe_command_nil(char *filename) {
    char *command;
    char **args;
    
size_t bufsize = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (getline(&command, &bufsize, file) != -1) {
        args = splitLine(command);
        exe_command(args);

        free(args);
    }

    fclose(file);
    free(command);
}
