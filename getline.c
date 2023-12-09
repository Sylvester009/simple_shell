#include "shell.h"

static char buffer[BUFSIZE];
static size_t buff_index = 0;

char *_getline(void) {
    size_t bufsize = 0;
    char *command = NULL;
    int i;

  ssize_t command_size;

    while (1) {
        if (buff_index == 0) {
            /* Buffer is empty, read more characters*/
            command_size = read(STDIN_FILENO, buffer, BUFSIZE);
            if (command_size < 0) {
                perror("error in reading command");
                exit(EXIT_FAILURE);
            } else if (comman_size == 0) {
                if (command != NULL) {
                    free(command);
                }
                return (NULL);
            }
            bufsize = (size_t)command_size;
        }

        i = buffer[buff_index];
        buff_index++;

        if (i == '\n' || i == EOF) {
            /* End of line or end of file*/
            if (command == NULL) {
                return (NULL);
            } else {
                command[bufsize] = '\0';
                buff_index = 0;
                return (command);
            }
        }

        /* Append character to the line*/
        command = realloc(command, bufsize + 2);
        if (command == NULL) {
            perror("error");
            exit(EXIT_FAILURE);
        }
        command[bufsize] = (char)i;
        bufsize++;
    }
}

