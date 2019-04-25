/*
** EPITECH PROJECT, 2018
** my_putstr
** File description:
** Day04 task02 my_putstr
*/

void my_putchar(char c);

int my_putstr(char const *str)
{
    if (!str) {
        my_putstr("(null)\0");
        return 84;
    }
    for (int i = 0; str[i] != '\0'; i = i + 1)
        my_putchar(str[i]);
    return 0;
}
