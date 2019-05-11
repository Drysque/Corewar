/*
** EPITECH PROJECT, 2018
** my_printf.c
** File description:
** recode the unix fonction "printf"
*/

#include <stdarg.h>
void my_putchar(char c);
int switch_flags(va_list ap, const char *str, int i);

void my_printf(const char *str, ...)
{
    va_list ap;

    va_start(ap, str);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != '%')
            my_putchar(str[i]);
        else
            i = switch_flags(ap, str, i);
    }
    va_end(ap);
}
