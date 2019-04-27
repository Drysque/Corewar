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

static void add_instruction(char **instruction_tab, op_list_t **op_list)
{
    op_list_t *new_op_list = malloc(sizeof(op_list_t));
    op_t *new_op = malloc(sizeof(op_t));

    new_op->mnemonique = instruction_tab[0];
    new_op->nbr_args = 0;
    my_strcpy(new_op->type, "0");
    new_op->code = 0;
    new_op->nbr_cycles = 0;
    new_op->comment = NULL;
    new_op_list->op = new_op;
    new_op_list->next_op = *op_list;
    *op_list = new_op_list;
}

void parse_instruction(char *instruction, label_t **label_list)
{
    char **tab = my_str_delim_array(instruction, " \t");

    if (tab == NULL) {
        my_printf("instruction failure: {%s}\n", instruction);
        exit(84);
    }
    if (tab[0][my_strlen(tab[0]) - 1] == LABEL_CHAR) {
        switch_label(tab[0], label_list);
        add_instruction(&tab[1], &(*label_list)->instruction_list);
    }
    else {
        add_instruction(tab, &(*label_list)->instruction_list);
    }
}
