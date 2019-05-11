/*
** EPITECH PROJECT, 2019
** parse_instruction.c
** File description:
** parses the instruction
*/

#include "my.h"
#include "asm.h"

static const char SEPAR_STR[] = {SEPARATOR_CHAR, ' ', '\t'};

static void check_valid_label(char *label_name)
{
    for (int i = 0; label_name[i]; i++)
        if (is_one_of_them(label_name[i], LABEL_CHARS) == false) {
            my_printf("\n\t\e[1m\e[31minvalid label name:\e[0m %s "
                "(unexpected '\e[5m%c\e[0m')\n\n",
                label_name, label_name[i]);
            exit(84);
        }
}

static void add_label(char *label_name, label_t **label_list)
{
    label_t *new_label = my_calloc(sizeof(label_t));

    check_valid_label(label_name);
    new_label->name = label_name;
    new_label->offset = offset_pos(0, GET);
    // printf("(added label %s: %d)\n", new_label->name, new_label->offset);
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
    op_list_t **op_list, header_t *header)
{
    char **tab = my_str_delim_array(clean_instruction(instruction), SEPAR_STR);
    int len = my_strlen(tab[0]);

    if (tab == NULL || len == 0)
        return;
    if (add_name_or_comment(instruction, header));
    else if (tab[0][len - 1] == LABEL_CHAR) {
        tab[0][len - 1] = 0;
        add_label(tab[0], label_list);
        add_instruction(&tab[1], op_list);
    }
    else
        add_instruction(tab, op_list);
}
