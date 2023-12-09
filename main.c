

#include "shell.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        
        char *line;
        char **args;
        int status;

      size_t bufsize = 0;

        do {
            printf("($) ");
            line = read_line();
            args = split_line(line);

            if (args[0] != NULL) {
                status = execute_command(args);
            } else {
                status = 1;  /* Empty command, continue the loop*/
            }

            free(line);
            free(args);
        } while (status);
    } else if (argc == 2) {
       
        char *filename = argv[1];
        char *line;
        char **args;

        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }

        
        while (getline(&line, &bufsize, file) != -1) {
            args = split_line(line);
            execute_command(args);

            free(args);
        }

        fclose(file);
        free(line);
    } else {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
