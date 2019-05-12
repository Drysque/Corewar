/*
** EPITECH PROJECT, 2019
** my_str_delim_array.c
** File description:
** sets a string into an array of strings
*/

#include <stdlib.h>
#include <stdbool.h>
char *my_strndup(char const *src, int n);

bool is_one_of_them(char c, char const *str)
{
    for (int i = 0; str[i]; i++)
        if (c == str[i])
            return true;
    return false;
}

static int delim_count(char const *str, char const *delims)
{
    int count = 0;

    for (int i = 0; str && str[i]; i++)
        if (!is_one_of_them(str[i], delims) &&
            (is_one_of_them(str[i + 1], delims) || !str[i + 1]))
            count++;
    return (count);
}

char **my_str_delim_array(char const *str, char const *delims)
{
    int count = delim_count(str, delims);
    char **array = malloc(sizeof(char *) * (count + 1));
    int length = 0;
    int a = 0;

    for (int i = 0; str && str[i]; length = 0, a++) {
        for (; str[i] && is_one_of_them(str[i], delims); i++);
        for (; str[i] && !is_one_of_them(str[i], delims); i++, length++);
        array[a] = my_strndup(&str[i - length], length);
    }
    array[count] = NULL;
    return (array);
}
