/*
** EPITECH PROJECT, 2019
** remove_quotes.c
** File description:
** removes the quotes
*/

#include "asm.h"
#include "my.h"

static void check_nothing_else(char *str)
{
    for (int i = 0; str[i] && str[i] != COMMENT_CHAR; i++)
        if (is_one_of_them(str[i], " \t") == false) {
            my_printf("\n\tline %d: \e[1m\e[31mSyntax error:\e[0m \e[5m%c\e[0m"
                " unexpected after quotes\n\n", line_counter(GET), str[i]);
            exit(84);
        }
}

void remove_quotes(char *str)
{
    if (str[0] == '\"') {
        for (int i = 1; str[i]; i++)
            if (str[i] == '\"') {
                str[i] = 0;
                check_nothing_else(&str[i + 1]);
                return;
            }
    } else
        my_error("Syntax error:\e[0m expected opening '\e[5m\"\e[0m'");
    my_error("Syntax error:\e[0m expected closing '\e[5m\"\e[0m'");
}
