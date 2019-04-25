/*
** EPITECH PROJECT, 2018
** my_put_nbr_long
** File description:
** Day03 task07 my_put_nbr_long
*/

void my_putchar(char c);

int my_put_nbr_long(long int nb)
{
    long int a = 0;
    int z = 0;

    if (nb < 0) {
        my_putchar('-');
        my_put_nbr_long(-nb);
        return (0);
    }
    z = nb % 10;
    a = nb / 10;
    if (a != 0)
        my_put_nbr_long(a);
    my_putchar(z + 48);
    return (0);
}
