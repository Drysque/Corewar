/*
** EPITECH PROJECT, 2018
** my_putstr_non_print.c
** File description:
** my_putstr that displays non-printable characters in their ascii value
*/

void my_putchar(char c);
int my_put_nbr_base(int nb, char *base);
int my_putstr(char const *str);

int my_putstr_non_print(char const *str)
{
    for (int i = 0; str[i] != '\0'; i = i + 1) {
        if (str[i] < 32) {
            my_putchar('\\');
            my_putchar('0');
        }
        if (str[i] < 8)
            my_putchar('0');
        if (str[i] < 32)
            my_put_nbr_base(str[i], "01234567");
        else if (str[i] == 127)
            my_putstr("\\177");
        else
            my_putchar(str[i]);
    }
    return (0);
}
