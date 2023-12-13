#include "shell.h"

char *command_path(const char *comm) {
    char *path = getenv("PATH");
    char *token, *temp_path;
    char *cmd_path = NULL;

    if (path == NULL) {
        fprintf(stderr, "./shell: No such file or directory\n");
        return NULL;
    }

    temp_path = strdup(path);
    if (temp_path == NULL) {
        perror("./shell: No such file or directory");
        exit(EXIT_FAILURE);
    }

    token = _strtok(temp_path, ":");
    while (token != NULL) {
        cmd_path = malloc(strlen(token) + strlen(comm) + 2);
        if (cmd_path == NULL) {
            perror("./shell: No such file or directory");
            exit(EXIT_FAILURE);
        }
        sprintf(cmd_path, "%s/%s", token, comm);

        if (access(cmd_path, F_OK | X_OK) == 0) {
            /* Found the executable in the current path*/
            free(temp_path);
            return (cmd_path);
        }

        free(cmd_path);
        token = _strtok(NULL, ":");
    }

    free(temp_path);
    fprintf(stderr, "./shell: No such file or directory %s\n", comm);
    return NULL;
}
