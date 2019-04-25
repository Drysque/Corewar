/*
** EPITECH PROJECT, 2018
** my_put_unsigned
** File description:
** Day03 task07 my_put_unsigned
*/

void my_putchar(char c);

int my_put_unsigned(unsigned int nb)
{
    unsigned int a = 0;
    unsigned int z = 0;

    z = nb % 10;
    a = nb / 10;
    if (a != 0)
        my_put_unsigned(a);
    my_putchar(z + 48);
    return (0);
}
