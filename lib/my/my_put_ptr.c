/*
** EPITECH PROJECT, 2018
** my_put_ptr
** File description:
** Day03 task07 my_put_ptr
*/

void my_putchar(char c);
int my_strlen(char const *str);
int my_putstr(char const *str);
void my_put_long_base(long int nb, char *base);

int my_put_ptr(void *nb)
{
    long int a = 0;

    if (!nb) {
        my_putstr("(nil)");
        return (0);
    }
    my_putstr("0x");
    a = (long int) nb;
    my_put_long_base(a, "0123456789abcdef");
}
