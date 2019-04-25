/*
** EPITECH PROJECT, 2018
** my_strcmp
** File description:
** Day06 task05 my_strcmp
*/

#include <stdbool.h>
int my_strlen(char const *str);

int my_strcmp_diff(char const *s1, char const *s2)
{
    int len1 = my_strlen(s1);
    int len2 = my_strlen(s2);

    if (!len1 || !len2)
        return false;
    if (len1 != len2)
        return false;
    for (int i = 0; s1[i]; i++)
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    return 0;
}

bool my_strcmp(char const *s1, char const *s2)
{
    int len1 = my_strlen(s1);
    int len2 = my_strlen(s2);

    if (!len1 || !len2)
        return false;
    if (len1 != len2)
        return false;
    for (int i = 0; s1[i]; i++)
        if (s1[i] != s2[i])
            return false;
    return true;
}

bool my_strncmp(char const *s1, char const *s2, int n)
{
    int len1 = my_strlen(s1);
    int len2 = my_strlen(s2);

    if (!len1 || !len2 || len1 < n || len2 < n)
        return false;
    for (int i = 0; i < n; i++)
        if (s1[i] != s2[i])
            return false;
    return true;
}
