/*
** EPITECH PROJECT, 2018
** my_strlen
** File description:
** Day04 task03 my_strlen
*/

int my_strlen(char const *str)
{
    int len = 0;

    for (; str && str[len]; len++);
    return (len);
}
