#include "shell.h"

extern char **environ;

int exe_command(char **args) {
    pid_t pid;
    int status;
    char *cmd_path;
     char **env_variable = environ;

    if (args[0] != NULL) {
        /* Handles built-in commands*/
        if (strcmp(args[0], "exit") == 0) {
            /* Handles the exit built-in command*/
            exit_shell(args);
        } else if (strcmp(args[0], "env") == 0) {
            /* Handle the env built-in command */
            env_variable = environ;
            while (*env_variable != NULL) {
                printf("%s\n", *env_variable);
                env_variable++;
            }
            return 1;
        }
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
