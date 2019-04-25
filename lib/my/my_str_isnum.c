/*
** EPITECH PROJECT, 2018
** my_str_isnum
** File description:
** function that returns 1 if it contains only digits.
*/

#include <stdbool.h>
int my_strlen(char const *str);

bool my_str_isnum(char const *str)
{
    if (!str)
        return false;
    if (!my_strlen(str))
        return false;
    for (int i = 0; str[i]; i++)
        if (str[i] < '0' || str[i] > '9')
            return false;
    return true;
}

bool my_char_isnum(char const c)
{
    if (c < '0' || c > '9')
        return false;
    return true;
}
