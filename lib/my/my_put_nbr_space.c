/*
** EPITECH PROJECT, 2018
** my_put_nbr_space
** File description:
** put a space before the int if it is neg, else a -
*/

void my_putchar(char c);
int my_put_nbr(int nb);

int my_put_nbr_space(int nb)
{
    if (nb >= 0)
        my_putchar(' ');
    my_put_nbr(nb);
}
