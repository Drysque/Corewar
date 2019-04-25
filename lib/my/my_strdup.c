/*
** EPITECH PROJECT, 2018
** my_strdup
** File description:
** allocate memory
*/

#include <stdlib.h>
int my_strlen(char const *str);

char *my_strdup(char const *src)
{
    char *str;
    int len;
    int i = 0;

    len = my_strlen(src);
    str = malloc((len + 1) * sizeof(char));
    if (str == NULL)
        return (NULL);
    str[len] = '\0';
    while (src[i]) {
        str[i] = src[i];
        i++;
    }
    return (str);
}
