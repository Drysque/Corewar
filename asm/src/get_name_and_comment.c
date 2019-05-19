/*
** EPITECH PROJECT, 2019
** add_name_or_comment.c
** File description:
** adds a name or a comment
*/

#include "asm.h"
#include "my.h"

static const char *ERRORS_NAME[] = {
    "Name is empty",
    "The name must be the first line of the program",
    "The program name is too long"};
static const char *ERRORS_COMMENT[] = {
    "Comment is empty",
    "\n\t\e[1m\e[31mWarning:\e[0m No comment is specified\n\n",
    "The comment is too long"};

static char *comment_warning(char *str)
{
    my_printf(ERRORS_COMMENT[1]);
    return str;
}

static char *get_comment(int fd, char *to_write)
{
    int index = 0;
    char *str = get_next_instruction(fd);
    int len = my_strlen(COMMENT_CMD_STRING);

    if (str == NULL)
        return comment_warning(NULL);
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
    } else
        return comment_warning(str);
}

static void get_name(int fd, char *to_write)
{
    int index = 0;
    char *str = get_next_instruction(fd);
    int len = my_strlen(NAME_CMD_STRING);

    if (str == NULL)
        my_error("File is empty");
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

char *get_name_and_comment(int fd, header_t *header)
{
    get_name(fd, header->prog_name);
    return get_comment(fd, header->comment);
}
