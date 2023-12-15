#include "shell.h"

/**
 * _strspn -length of a prefix substring
 * @str: string to be searched
 * @accept: string containing characters to match
 *
 * Return: no of bytes in the initial segment of `str` which are part of `accept`
 */
int _strspn(char *str, char *accept) {
    int i = 0;
    int match = 0;

    while (str[i] != '\0') {
        if (_strchr(accept, str[i]) == NULL)
            break;
        match++;
        i++;
    }
    return match;
}

/**
 * _strcspn - computes segment of `str` which consists of characters not in `reject`
 * @str: string to be searched
 * @reject: string containing characters to reject
 *
 * Return: index at which a char in `str` exists in `reject`
 */
int _strcspn(char *str, char *reject) {
    int len = 0, i;

    for (i = 0; str[i] != '\0'; i++) {
        if (_strchr(reject, str[i]) != NULL)
            break;
        len++;
    }
    return len;
}

/**
 * _strchr - locates a char in a string
 * @s: string to be searched
 * @c: char to be checked
 *
 * Return: pointer to the first occurrence of `c` in `s`
 */
char *custom_strchr(char *s, char c) {
    int i = 0;

    for (; s[i] != c && s[i] != '\0'; i++)
        ;
    if (s[i] == c)
        return (s + i);
    else
        return NULL;
}
