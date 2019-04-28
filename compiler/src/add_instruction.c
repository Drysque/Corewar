/*
** EPITECH PROJECT, 2019
** add_instruction.c
** File description:
** adds an instruction
*/

#include "asm.h"
#include "my.h"

void add_instruction(char **instr_tab, op_list_t **op_list)
{
    op_list_t *new_op_list = malloc(sizeof(op_list_t));
    op_t *new_op = malloc(sizeof(op_t));
    char **args = my_str_delim_array(instr_tab[1], (char[]){SEPARATOR_CHAR, 0});

    new_op->mnemonique = instr_tab[0];
    my_strcpy(new_op->type, "0");//
    new_op->nbr_args = 0;//
    new_op->code = 0;//
    new_op->nbr_cycles = 0;//
    new_op->comment = NULL;//
    new_op_list->op = new_op;
    new_op_list->next_op = *op_list;
    *op_list = new_op_list;
}
