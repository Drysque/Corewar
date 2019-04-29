/*
** EPITECH PROJECT, 2019
** add_instruction.c
** File description:
** adds an instruction
*/

#include "asm.h"
#include "my.h"

void get_args_type(char *type, char **instr_tab)
{
    for (int i = 0; instr_tab[i]; i++) {
        if (instr_tab[i][0] == 'r') {
            my_printf("0x%x ", my_getnbr(&instr_tab[i][1]));
            type[i] = 01;
        }
        else if (instr_tab[i][0] == '%') {
            my_printf("0x00 0x00 0x00 0x%x ", my_getnbr(&instr_tab[i][1]));
            type[i] = 10;
        }
        else {
            my_printf("0x00 0x%x ", my_getnbr(instr_tab[i]));
            type[i] = 11;
        }
    }
    my_printf("\n");
}

void add_instruction(char **instr_tab, op_list_t **op_list)
{
    op_list_t *new_op_list = malloc(sizeof(op_list_t));
    op_t *new_op = malloc(sizeof(op_t));
    char **args = my_str_delim_array(instr_tab[1], (char[]){SEPARATOR_CHAR, 0});

    new_op->mnemonique = instr_tab[0];
    for (int i = 0; op_tab[i].mnemonique != 0; i++) {
        if (my_strcmp(op_tab[i].mnemonique, new_op->mnemonique)) {
            new_op->code = op_tab[i].code;
            new_op->nbr_cycles = op_tab[i].nbr_cycles;
            new_op->comment = op_tab[i].comment;
            new_op->nbr_args = my_tablen((char const **) args);
            if (new_op->nbr_args != op_tab[i].nbr_args) {
                my_printf("wrong number of arguments for instruction %s (%s)",
                instr_tab[0], instr_tab[1]);
                exit(84);
            }
            get_args_type(new_op->type, args);
        }
    }
    new_op_list->op = new_op;
    new_op_list->next_op = *op_list;
    *op_list = new_op_list;
}
