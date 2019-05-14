/*
** EPITECH PROJECT, 2019
** add_name_or_comment.c
** File description:
** adds a name or a comment
*/

#include "asm.h"
#include "my.h"

static const char *ERRORS_NAME[] = {
    "\n\t\e[1m\e[31mNo name is specified\e[0m\n\n",
    "\n\t\e[1m\e[31mThe name must be the first line of the program\e[0m\n\n",
    "\n\t\e[1m\e[31mThe program name is too long\e[0m\n\n"};
static const char *ERRORS_COMMENT[] = {
    "\n\t\e[1m\e[31mNo comment is specified\e[0m\n\n",
    "\n\t\e[1m\e[31mThe comment must follow the name\e[0m\n\n",
    "\n\t\e[1m\e[31mThe comment is too long\e[0m\n\n"};
static const char **ERRORS[] = {ERRORS_NAME, ERRORS_COMMENT};
static const int LENGHTS[] = {PROG_NAME_LENGTH, COMMENT_LENGTH};

static void remove_quotes(char *str)
{
    if (str[0] == '\"') {
        for (int i = 1; str[i]; i++)
            if (str[i] == '\"') {
                str[i] = 0;
                return;
            }
    } else {
        my_printf("\n\t\e[1m\e[31mSyntax error:\e[0m expected opening "
            "'\e[5m%c\e[0m'\n\n", '\"');
        exit(84);
    }
    my_printf("\n\t\e[1m\e[31mSyntax error:\e[0m expected closing "
        "'\e[5m%c\e[0m'\n\n", '\"');
    exit(84);
}

static void get_info(int fd, char *to_get, char *to_write, int status)
{
    int index = 0;
    char *str = get_next_instruction(fd);
    int len = my_strlen(to_get);

    if (str == NULL)
        my_error("\n\t\e[1m\e[97m\e[101m\e[5mFile is empty\e[0m\n\n");
    for (; str[index] && is_one_of_them(str[index], " \t"); index++);
    if (my_strncmp(&str[index], to_get, len)) {
        index += len;
        for (; str[index] && is_one_of_them(str[index], " \t"); index++);
        if (str[index] == '\0')
            my_error(ERRORS[status][0]);
        remove_quotes(&str[index++]);
        if (my_strlen(&str[index]) > LENGHTS[status])
            my_error(ERRORS[status][2]);
        my_strcpy(to_write, &str[index]);
    } else
        my_error(ERRORS[status][1]);
    free(str);
}

void get_name_or_comment(int fd, header_t *header)
{
    get_info(fd, NAME_CMD_STRING, header->prog_name, 0);
    get_info(fd, COMMENT_CMD_STRING, header->comment, 1);
}
