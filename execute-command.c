#include "shell.h"

extern char **environ;

int exe_command(char **args) {
    pid_t pid;
    int status;
    char *cmd_path;
    char **env_var;

    if (args[0] != NULL) {
        if (strcmp(args[0], "exit") == 0) {
            exit_shell(args);
        } else if (strcmp(args[0], "env") == 0) {
            for (env_var = environ; *env_var != NULL; env_var++) {
                printf("%s\n", *env_var);
            }
            return 1;
        } else if (strcmp(args[0], "setenv") == 0) {
            set_env_var(args);
            return 1;
        } else if (strcmp(args[0], "unsetenv") == 0) {
            unset_env_var(args);
            return 1;
        }
    }

    cmd_path = command_path(args[0]);

    if (cmd_path == NULL) {
        fprintf(stderr, "Shell: Command not found: %s\n", args[0]);
        return 1;
    }

    pid = fork();
    if (pid == 0) {
        if (execve(cmd_path, args, environ) == -1) {
            perror("error");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("error");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    free(cmd_path);
    return 1;
}
