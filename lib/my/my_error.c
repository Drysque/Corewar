/*
** EPITECH PROJECT, 2019
** my_error.c
** File description:
** prints an error and quits
*/

#include <stdlib.h>

int line_counter(int status);
void my_printf(const char *str, ...);

void my_error_str(const char *error_fmt, const char *error_str)
{
    my_printf("\n\tline %d: \e[1m\e[31m", line_counter(0));
    my_printf(error_fmt, error_str);
    my_printf("\e[0m\n\n");
    exit(84);
}

void my_error(const char *error_fmt)
{
    my_printf("\n\tline %d: \e[1m\e[31m", line_counter(0));
    my_printf(error_fmt);
    my_printf("\e[0m\n\n");
    exit(84);
}
