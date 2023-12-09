#include "shell.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        
        char *command;
        char **args;
        int status;


        do {
            printf("$ ");
            command = read_command();
            args = splitLine(command);

            if (args[0] != NULL) {
                status = exe_command(args);
            } else {
                status = 1;  /* Empty command, continue the loop*/
            }

            free(command);
            free(args);
        } while (status);
    } else if (argc == 2) {
       
        char *filename = argv[1];
        char *command;
        char **args;

        size_t bufsize = 0;

        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error");
            return (FAILURE);
        }

        
        while (getline(&command, &bufsize, file) != -1) {
            args = splitLine(command);
            exe_command(args);

            free(args);
        }

        fclose(file);
        free(command);
    } else {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return (EXIT_FAILURE);
    }

    return (SUCCESS);
}
