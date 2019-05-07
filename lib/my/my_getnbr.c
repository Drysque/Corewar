/*
** EPITECH PROJECT, 2018
** my_getnbr
** File description:
** task05
*/

#include <sys/types.h>

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

char my_str_to_char(char const *str)
{
    int i = 0;
    char nbr = 0;
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

char my_str_to_int16(char const *str)
{
    u_int16_t i = 0;
    char nbr = 0;
    u_int16_t minus = 0;

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
