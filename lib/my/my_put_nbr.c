/*
** EPITECH PROJECT, 2018
** my_put_nbr
** File description:
** Day03 task07 my_put_nbr
*/

void my_putchar(char c);
int my_putstr(char const *str);

int my_put_nbr(int nb)
{
    int a = 0;
    int z = 0;

    if (nb == -2147483648) {
        my_putstr("-2147483648");
        return (0);
    }
    if (nb < 0) {
        my_putchar('-');
        my_put_nbr(-nb);
        return (0);
    }
    z = nb % 10;
    a = nb / 10;
    if (a != 0)
        my_put_nbr(a);
    my_putchar(z + 48);
    return (0);
}
