/*
** EPITECH PROJECT, 2019
** my_error.c
** File description:
** prints an error and quits
*/

#include <stdlib.h>

void my_printf(const char *str, ...);

void my_error(const char *error)
{
    my_printf(error);
    exit(84);
}
