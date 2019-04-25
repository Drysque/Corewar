/*
** EPITECH PROJECT, 2018
** format_switches.c
** File description:
** contains the switche for the "special flag" function
*/

#include <stdarg.h>
void my_putchar(char c);
int my_putstr(char const *str);
int my_put_nbr_space(int nb);
int my_put_nbr_pos(int nb);
int my_put_nbr_base(int nb, char *base);
int my_put_unsigned(unsigned int nb);
int my_put_ptr(void *nb);
void switch_letters(va_list ap, char c);
void switch_numbers(va_list ap, char c);

int switch_space_base(va_list ap, char d, int i)
{
    switch (d) {
    case 'o': my_put_nbr_base(va_arg(ap, int), "01234567");
        break;
    case 'x': my_put_nbr_base(va_arg(ap, int), "0123456789abcdef");
        break;
    case 'X': my_put_nbr_base(va_arg(ap, int), "0123456789ABCDEF");
        break;
    default: break;
    }
    return (i);
}

int switch_space_numbers(va_list ap, char d, char e, int i)
{
    switch (d) {
    case 'u': my_put_unsigned(va_arg(ap, unsigned int));
        break;
    case 'd': my_put_nbr_space(va_arg(ap, int));
        break;
    case 'i': my_put_nbr_space(va_arg(ap, int));
        break;
    case 'p': my_putchar(' ');
        my_put_ptr(va_arg(ap, void *));
        break;
    case 'b': my_putstr("% b");
        break;
    case ' ': switch_space_numbers(ap, e, '\0', i);
        switch_space_base(ap, e, i);
        i++;
        break;
    default: break;
    }
    return (i);
}

void switch_numbers_sharp(va_list ap, char d)
{
    switch (d) {
    case 'o': my_putstr("0");
        my_put_nbr_base(va_arg(ap, int), "01234567");
        break;
    case 'x': my_putstr("0x");
        my_put_nbr_base(va_arg(ap, int), "0123456789abcdef");
        break;
    case 'X': my_putstr("0X");
        my_put_nbr_base(va_arg(ap, int), "0123456789ABCDEF");
        break;
    case 'b': my_putstr("%#b");
        break;
    default: switch_letters(ap, d);
        switch_numbers(ap, d);
        break;
    }
}

void switch_numbers_plus(va_list ap, char d)
{
    switch (d) {
    case 'u': my_put_unsigned(va_arg(ap, unsigned int));
        break;
    case 'd': my_put_nbr_pos(va_arg(ap, int));
        break;
    case 'i': my_put_nbr_pos(va_arg(ap, int));
        break;
    case 'p': my_putchar('+');
        my_put_ptr(va_arg(ap, void *));
        break;
    case 'b': my_putstr("%+b");
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

int switch_special(va_list ap, char const *str, int i)
{
    int j = i;

    switch (str[j + 1]) {
    case '#': switch_numbers_sharp(ap, str[j + 2]);
        i++;
        break;
    case ' ': i = switch_space_numbers(ap, str[j + 2], str[j + 3], i);
        i = switch_space_base(ap, str[j + 2], i);
        i++;
        break;
    case '+': switch_numbers_plus(ap, str[j + 2]);
        switch_letters(ap, str[j + 2]);
        i++;
        break;
    case '0': switch_letters(ap, str[j + 2]);
        switch_numbers(ap, str[j + 2]);
        i++;
        break;
    }
    return (i);
}
