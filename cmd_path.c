#include "shell.h"

char *find_command_path(const char *comm) {
    char *path = getenv("PATH");
    char *token, *temp_path;
    char *command_path = NULL;

    if (path == NULL) {
        fprintf(stderr, "Shell: PATH environment variable not set\n");
        return NULL;
    }

    temp_path = strdup(path);
    if (temp_path == NULL) {
        perror("shell");
        exit(EXIT_FAILURE);
    }

    token = strtok(temp_path, ":");
    while (token != NULL) {
        command_path = malloc(strlen(token) + strlen(comm) + 2);
        if (command_path == NULL) {
            perror("shell");
            exit(EXIT_FAILURE);
        }
        sprintf(command_path, "%s/%s", token, comm);

        if (access(command_path, X_OK) == 0) {
            /* Found the executable in the current path*/
            free(temp_path);
            return command_path;
        }

        free(command_path);
        token = strtok(NULL, ":");
    }

    free(temp_path);
    fprintf(stderr, "Shell: Command not found in PATH: %s\n", comm);
    return NULL;
}
