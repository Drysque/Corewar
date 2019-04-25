/*
** EPITECH PROJECT, 2018
** my_getnbr
** File description:
** task05
*/

int my_getnbr(char const *str)
{
    int i = 0;
    int nbr = 0;
    int minus = 0;

    for (; str[i] == '-'; i++, minus++);
    for (minus %= 2; str[i] >= '0' && str[i] <= '9'; i++) {
        nbr = nbr * 10 + str[i] - '0';
        if (i - minus > 9)
            return 0;
    }
    if (minus)
        nbr *= -1;
    return nbr;
}
