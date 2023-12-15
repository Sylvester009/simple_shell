#include "shell.h"

/**
 *_strlen - counts length of string
 *@string: string to be counted
 *
 * Return: string length
 */

size_t _strlen(const char *string)
{
    size_t len = 0;

    if (string != NULL) {
        while (string[len] != '\0') {
            len++;
        }
    }

    return len;
}

/**
 * handle_interrupt - handles the signal raised by CTRL-C
 * @signum: signal number
 *
 * Return: void
 */
void handle_interrupt(int signum)
{
	if (signum == SIGINT)
		print("\n$ ", STDIN_FILENO);
}
