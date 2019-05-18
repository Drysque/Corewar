/*
** EPITECH PROJECT, 2019
** line_counter.c
** File description:
** counts the lines
*/

int line_counter(int status)
{
    static int line = 0;

    if (status)
        line++;
    return line;
}
