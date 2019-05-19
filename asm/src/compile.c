/*
** EPITECH PROJECT, 2019
** compile.c
** File description:
** starts the compilation
*/

#include "asm.h"
#include "my.h"

static void check_info_redef(char *str)
{
    int index = 0;
    char *comment_str = COMMENT_CMD_STRING;

    for (; str[index] && is_one_of_them(str[index], " \t"); index++);
    if (my_strncmp(&str[index], NAME_CMD_STRING, my_strlen(NAME_CMD_STRING)))
        my_error("Name can only be defined once");
    if (my_strncmp(&str[index], comment_str, my_strlen(comment_str)))
        my_error("Comment can only be defined once");
}

static void check_label_is_def(label_t *label_list, char *label)
{
    while (label_list) {
        if (my_strcmp(label_list->name, label))
            return;
        label_list = label_list->next_label;
    }
    my_error_str("Unknown label:\e[0m %s", label);
}

static void check_label_nodef(label_t *label_list)
{
    op_need_label_t *list = add_need_label(NULL, GET, 0, 0);

    while (list) {
        check_label_is_def(label_list, list->label);
        list = list->next_op;
    }
}

void compile(int fd, char *new_file)
{
    char *str = NULL;
    header_t *header = my_calloc(sizeof(header_t));
    label_t *label_list = NULL;
    op_list_t *op_list = NULL;

    str = get_name_and_comment(fd, header);
    while (str != NULL) {
        check_info_redef(str);
        parse_instruction(str, &label_list, &op_list);
        free(str);
        str = get_next_instruction(fd);
    }
    check_label_nodef(label_list);
    write_in_file(header, label_list, op_list, new_file);
    free_all(header, label_list, op_list);
}
