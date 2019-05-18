/*
** EPITECH PROJECT, 2019
** parse_instruction.c
** File description:
** parses the instruction
*/

#include "my.h"
#include "asm.h"

static const char SEPAR_STR[] = {SEPARATOR_CHAR, ' ', '\t'};

static void check_valid_label(char *label_name, label_t *label_list)
{
    for (int i = 0; label_name[i]; i++)
        if (is_one_of_them(label_name[i], LABEL_CHARS) == false) {
            my_printf("\n\t\e[1m\e[31mInvalid label name:\e[0m %s "
                "(unexpected '\e[5m%c\e[0m')\n\n",
                label_name, label_name[i]);
            exit(84);
        }
    while (label_list) {
        if (my_strcmp(label_list->name, label_name))
            my_error_str("Label already defined:\e[0m %s", label_name);
        label_list = label_list->next_label;
    }
}

static void add_label(char *label_name, label_t **label_list)
{
    label_t *new_label = my_calloc(sizeof(label_t));

    check_valid_label(label_name, *label_list);
    new_label->name = label_name;
    new_label->offset = offset_pos(0, GET);
    new_label->next_label = *label_list;
    *label_list = new_label;
}

static char *clean_instruction(char *instruction)
{
    for (int i = 0; instruction && instruction[i]; i++)
        if (instruction[i] == COMMENT_CHAR)
            instruction[i] = 0;
    return instruction;
}

void parse_instruction(char *instruction, label_t **label_list,
    op_list_t **op_list)
{
    char **tab = my_str_delim_array(clean_instruction(instruction), SEPAR_STR);
    int len = my_strlen(tab[0]);

    if (tab == NULL || len == 0)
        return;
    if (tab[0][len - 1] == LABEL_CHAR) {
        tab[0][len - 1] = 0;
        add_label(tab[0], label_list);
        add_instruction(&tab[1], op_list);
    }
    else
        add_instruction(tab, op_list);
}
