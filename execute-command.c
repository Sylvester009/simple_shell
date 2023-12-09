#include "shell.h"

extern char **environ;

int exe_command(char **args) {
    pid_t pid;
    int status;
    char *cmd_path;

    if (args[0] != NULL && strcmp(args[0], "exit") == 0) {
        /* Handles the exit built-in command*/
        printf("Shell: Exiting...\n");
        exit(EXIT_SUCCESS);
    }

    cmd_path = command_path(args[0]);

    if (cmd_path == NULL) {
        fprintf(stderr, "Shell: Command not found: %s\n", args[0]);
        return (1);
    }

    pid = fork();
    if (pid == 0) {
        /* Child process */
        if (execve(cmd_path, args, environ) == -1) {
            perror("error");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Forking error */
        perror("error");
    } else {
        /* Parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    free(cmd_path);
    return (1);
}
