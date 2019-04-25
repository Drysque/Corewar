/*
** EPITECH PROJECT, 2018
** my_put_nbr
** File description:
** my_put_nbr with a space if positive
*/

void my_putchar(char c);
int my_putstr(char const *str);
int my_put_nbr(int nb);

int my_put_nbr_pos(int nb)
{
    if (nb >= 0)
        my_putchar('+');
    my_put_nbr(nb);
}
