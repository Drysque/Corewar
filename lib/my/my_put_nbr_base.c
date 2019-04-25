/*
** EPITECH PROJECT, 2018
** my_put_nbr_base
** File description:
** Day03 task07 my_put_nbr_base
*/

void my_putchar(char c);
int my_strlen(char const *str);

int my_put_nbr_base(int nb, char *base)
{
    int a = 0;
    int z = 0;

    if (nb < 0) {
        my_putchar('-');
        my_put_nbr_base(-nb, base);
        return (0);
    }
    a = nb / my_strlen(base);
    z = nb % my_strlen(base);
    if (a != 0)
        my_put_nbr_base(a, base);
    my_putchar(base[z]);
    return (0);
}
