/*
** EPITECH PROJECT, 2018
** my_put_long_base.c
** File description:
** displays a long number in a specified base
*/

void my_putchar(char c);
int my_strlen(char const *str);

void my_put_long_base(long int nb, char *base)
{
    long int a = 0;
    int z = 0;

    if (nb < 0) {
        my_putchar('-');
        my_put_long_base(-nb, base);
        return;
    }
    a = nb / my_strlen(base);
    z = nb % my_strlen(base);
    if (a != 0)
        my_put_long_base(a, base);
    my_putchar(base[z]);
}
