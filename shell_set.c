#include "shell.h"

void exe_command_i(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("($) ");
        line = read_line();
        args = split_line(line);

        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                free(line);
                free(args);
                exit(EXIT_SUCCESS);
            }

            status = execute_command(args);
        } else {
            status = 1;  /** Empty command, continue the loop*/
        }

        free(line);
        free(args);
    } while (status);
}

void exe_command_nil(char *filename) {
    char *line;
    char **args;
    int status;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    size_t bufsize = 0;
    while (getline(&line, &bufsize, file) != -1) {
        args = split_line(line);
        status = execute_command(args);

        free(args);
    }

    fclose(file);
    free(line);
}
