/*
** EPITECH PROJECT, 2018
** my_tablen
** File description:
** returns the len of a tab
*/

int my_tablen(char const **tab)
{
    int len = 0;

    for (; tab && tab[len]; len++);
    return (len);
}
