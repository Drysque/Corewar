/*
** EPITECH PROJECT, 2018
** defined function
** File description:
** Day07 library
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
