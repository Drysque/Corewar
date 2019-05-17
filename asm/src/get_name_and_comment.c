/*
** EPITECH PROJECT, 2019
** add_name_or_comment.c
** File description:
** adds a name or a comment
*/

#include "asm.h"
#include "my.h"

static const char *ERRORS_NAME[] = {
    "\n\t\e[1m\e[31mName is empty\e[0m\n\n",
    "\n\t\e[1m\e[31mThe name must be the first line of the program\e[0m\n\n",
    "\n\t\e[1m\e[31mThe program name is too long\e[0m\n\n"};
static const char *ERRORS_COMMENT[] = {
    "\n\t\e[1m\e[31mComment is empty\e[0m\n\n",
    "\n\t\e[1m\e[31mWarning:\e[0m No comment is specified\n\n",
    "\n\t\e[1m\e[31mThe comment is too long\e[0m\n\n"};

static void check_nothing_else(char *str)
{
    for (int i = 0; str[i] && str[i] != COMMENT_CHAR; i++)
        if (is_one_of_them(str[i], " \t") == false) {
            my_printf("\n\t\e[1m\e[31mSyntax error:\e[0m "
            "\e[5m%c\e[0m unexpected after quotes\n\n", str[i]);
            exit(84);
        }
}

static void remove_quotes(char *str)
{
    if (str[0] == '\"') {
        for (int i = 1; str[i]; i++)
            if (str[i] == '\"') {
                str[i] = 0;
                check_nothing_else(&str[i + 1]);
                return;
            }
    } else {
        my_error("\n\t\e[1m\e[31mSyntax error:\e[0m expected opening "
            "'\e[5m\"\e[0m'\n\n");
    }
    my_error("\n\t\e[1m\e[31mSyntax error:\e[0m expected closing "
        "'\e[5m\"\e[0m'\n\n");
}

static void get_name(int fd, char *to_write)
{
    int index = 0;
    char *str = get_next_instruction(fd);
    int len = my_strlen(NAME_CMD_STRING);

    if (str == NULL)
        my_error("\n\t\e[1m\e[97m\e[101m\e[5mFile is empty\e[0m\n\n");
    for (; str[index] && is_one_of_them(str[index], " \t"); index++);
    if (my_strncmp(&str[index], NAME_CMD_STRING, len)) {
        index += len;
        for (; str[index] && is_one_of_them(str[index], " \t"); index++);
        if (str[index] == '\0')
            my_error(ERRORS_NAME[0]);
        remove_quotes(&str[index++]);
        if (my_strlen(&str[index]) > PROG_NAME_LENGTH)
            my_error(ERRORS_NAME[2]);
        my_strcpy(to_write, &str[index]);
    } else
        my_error(ERRORS_NAME[1]);
    free(str);
}

static char *get_comment(int fd, char *to_write)
{
    int index = 0;
    char *str = get_next_instruction(fd);
    int len = my_strlen(COMMENT_CMD_STRING);

    if (str == NULL) {
        my_printf(ERRORS_COMMENT[1]);
        return NULL;
    }
    for (; str[index] && is_one_of_them(str[index], " \t"); index++);
    if (my_strncmp(&str[index], COMMENT_CMD_STRING, len)) {
        index += len;
        for (; str[index] && is_one_of_them(str[index], " \t"); index++);
        if (str[index] == '\0')
            my_error(ERRORS_COMMENT[0]);
        remove_quotes(&str[index++]);
        if (my_strlen(&str[index]) > COMMENT_LENGTH)
            my_error(ERRORS_COMMENT[2]);
        my_strcpy(to_write, &str[index]);
        free(str);
        return get_next_instruction(fd);
    } else {
        my_printf(ERRORS_COMMENT[1]);
        return str;
    }
}

char *get_name_and_comment(int fd, header_t *header)
{
    get_name(fd, header->prog_name);
    return get_comment(fd, header->comment);
}
