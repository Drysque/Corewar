/*
** EPITECH PROJECT, 2019
** parse_instruction.c
** File description:
** parses the instruction
*/

#include "my.h"
#include "asm.h"

static void switch_label(char *label_name, label_t **label_list)
{
    label_t *new_label = create_label(label_name);

    new_label->next_label = *label_list;
    *label_list = new_label;
}

void parse_instruction(char *instruction, label_t **label_list)
{
    char **tab = my_str_delim_array(instruction, " \t");

    if (tab == NULL) {
        my_printf("instruction failure: {%s}\n", instruction);
        exit(84);
    }
    if (tab[0][my_strlen(tab[0]) - 1] == LABEL_CHAR) {
        tab[0][my_strlen(tab[0]) - 1] = 0;
        switch_label(tab[0], label_list);
        add_instruction(&tab[1], &(*label_list)->instruction_list);
    }
    else {
        add_instruction(tab, &(*label_list)->instruction_list);
    }
}
