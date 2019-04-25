/*
** EPITECH PROJECT, 2018
** my_put_long_unsigned
** File description:
** Day03 task07 my_put_long_unsigned
*/

void my_putchar(char c);

int my_put_long_unsigned(long unsigned int nb)
{
    long unsigned int a = 0;
    long unsigned int z = 0;

    z = nb % 10;
    a = nb / 10;
    if (a != 0)
        my_put_long_unsigned(a);
    my_putchar(z + 48);
    return (0);
}
