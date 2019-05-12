/*
** EPITECH PROJECT, 2018
** switch_flags.c
** File description:
** core thar redirects to different switchs
*/

#include <stdlib.h>
#include <stdarg.h>
void my_putchar(char c);
int my_putstr(char const *str);
int my_putstr_non_print(char const *str);
void my_put_long_base(long int nb, char *base);
int my_put_long_unsigned(long unsigned int nb);
int my_put_nbr(int nb);
int my_put_nbr_base(int nb, char *base);
int my_put_nbr_long(long int nb);
int my_put_unsigned(unsigned int nb);
int my_put_ptr(void *nb);
int switch_special(va_list ap, char const *str, int i);

void switch_letters(va_list ap, char c)
{
    switch (c) {
    case 'c': my_putchar(va_arg(ap, int));
        break;
    case 's': my_putstr(va_arg(ap, char *));
        break;
    case 'S': my_putstr_non_print(va_arg(ap, char *));
        break;
    case '%': my_putchar('%');
        break;
    case '\0': my_putstr("%");
    }
}

void switch_numbers(va_list ap, char c)
{
    switch (c) {
    case 'u': my_put_unsigned(va_arg(ap, unsigned int));
        break;
    case 'd': my_put_nbr(va_arg(ap, int));
        break;
    case 'i': my_put_nbr(va_arg(ap, int));
        break;
    case 'p': my_put_ptr(va_arg(ap, void *));
        break;
    case 'b': my_put_nbr_base(va_arg(ap, int), "01");
        break;
    case 'o': my_put_nbr_base(va_arg(ap, int), "01234567");
        break;
    case 'x': my_put_nbr_base(va_arg(ap, int), "0123456789abcdef");
        break;
    case 'X': my_put_nbr_base(va_arg(ap, int), "0123456789ABCDEF");
        break;
    default: break;
    }
}

void switch_numbers_long(va_list ap, char d)
{
    switch (d) {
    case 'u': my_put_long_unsigned(va_arg(ap, long unsigned int));
        break;
    case 'd': my_put_nbr_long(va_arg(ap, long int));
        break;
    case 'i': my_put_nbr_long(va_arg(ap, long int));
        break;
    case 'b': my_put_long_base(va_arg(ap, long int), "01");
        break;
    case 'o': my_put_long_base(va_arg(ap, long int), "01234567");
        break;
    case 'x': my_put_long_base(va_arg(ap, long int), "0123456789abcdef");
        break;
    case 'X': my_put_long_base(va_arg(ap, long int), "0123456789ABCDEF");
        break;
    default: break;
    }
}

int switch_bonus(va_list ap, char const *str, int i)
{
    int j = i;

    switch (str[j + 1]) {
    case 'l': switch_numbers_long(ap, str[j + 2]);
        i++;
        break;
    default: break;
    }
    return (i);
}

int switch_flags(va_list ap, const char *str, int i)
{
    switch_letters(ap, str[i + 1]);
    switch_numbers(ap, str[i + 1]);
    i = switch_bonus(ap, str, i);
    i = switch_special(ap, str, i);
    return (++i);
}
