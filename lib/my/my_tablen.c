/*
** EPITECH PROJECT, 2018
** my_tablen
** File description:
** returns the len of a tab
*/

int my_tablen(const char **tab)
{
    int len = 0;

    for (; tab && tab[len]; len++);
    return (len);
}
