/*
** EPITECH PROJECT, 2019
** my_strndup.c
** File description:
** strncpy
*/

#include <stdlib.h>

char *my_strndup(char const *src, int n)
{
    int i = 0;
    char *dest = malloc(sizeof(char) * (n + 1));

    if (dest == NULL)
        return NULL;
    for (i = 0; src[i] && i < n; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}
