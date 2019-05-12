/*
** EPITECH PROJECT, 2018
** my_strdup
** File description:
** allocate memory
*/

#include <stdlib.h>
int my_strlen(char const *new);

char *my_strdup(char const *src)
{
    int len = my_strlen(src);
    char *new = malloc((len + 1) * sizeof(char));
    int i = 0;

    if (new == NULL)
        return NULL;
    for (; src[i]; i++)
        new[i] = src[i];
    new[len] = '\0';
    return (new);
}
