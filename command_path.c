#include "shell.h"

char *command_path(const char *comm) {
    char *path = getenv("PATH");
    char *token, *temp_path;
    char *cmd_path = NULL;

    if (path == NULL) {
        fprintf(stderr, "Shell: No PATH variable found\n");
        return NULL;
    }

    temp_path = strdup(path);
    if (temp_path == NULL) {
        perror("Shell");
        exit(EXIT_FAILURE);
    }

    token = _strtok(temp_path, ":");

    while (token != NULL) {
        
        cmd_path = malloc(strlen(token) + strlen(comm) + 2);
        if (cmd_path == NULL) {
            perror("Shell");
            exit(EXIT_FAILURE);
        }

        sprintf(cmd_path, "%s/%s", token, comm);

        if (access(cmd_path, F_OK | X_OK) == 0) {
            
            free(temp_path);
            return cmd_path;
        }

        free(cmd_path); 
        token = _strtok(NULL, ":");
    }

    free(temp_path);
    fprintf(stderr, "Shell: No such file or directory: %s\n", comm);
    return NULL;
}
