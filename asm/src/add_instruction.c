/*
** EPITECH PROJECT, 2019
** add_instruction.c
** File description:
** adds an instruction
*/

#include "asm.h"
#include "my.h"

void get_args_type(char *type, void **args, char **instr_tab)
{
    for (int i = 0; instr_tab[i]; i++) {
        if (instr_tab[i][0] == 'r') {
            type[i] = 0b01;
            // my_printf("0x%x ", my_getnbr(&instr_tab[i][1]));
            args[i] = malloc(sizeof(char));
            *((char *) args[i]) = my_str_to_char(&instr_tab[i][1]);
        }
        else if (instr_tab[i][0] == '%') {//direct
            // my_printf("0x00 0x00 0x00 0x%x ", my_getnbr(&instr_tab[i][1]));
            type[i] = 0b10;
            args[i] = malloc(sizeof(int));
            *((int *) args[i]) = my_getnbr(&instr_tab[i][1]);
            if (instr_tab[i][1] == LABEL_CHAR) {
                // type[i] = 0b11;
                args[i] = malloc(sizeof(u_int16_t));
                *((u_int16_t *) args[i]) = 0;
            }
        }
        else {
            type[i] = 0b11;
            args[i] = malloc(sizeof(u_int16_t));
            // my_printf("0x00 0x%x ", my_getnbr(instr_tab[i]));
            *((u_int16_t *) args[i]) = my_str_to_int16(instr_tab[i]);
        }
    }
    // my_printf("\n");
}

void add_instruction(char **instr_tab, op_list_t **op_list)
{
    op_list_t *new_op = my_calloc(sizeof(op_list_t));
    char **args = my_str_delim_array(instr_tab[1], (char[]){SEPARATOR_CHAR, 0});

    // new_op->mnemonique = instr_tab[0];
    for (int i = 0; op_tab[i].mnemonique != 0; i++) {
        if (my_strcmp(op_tab[i].mnemonique, instr_tab[0])) {
            new_op->code = op_tab[i].code;
            // new_op->nbr_cycles = op_tab[i].nbr_cycles;
            // new_op->comment = op_tab[i].comment;
            // new_op->nbr_args = my_tablen((char const **) args);
            if (my_tablen((char const **) args) != op_tab[i].nbr_args) {
                my_printf("wrong number of arguments for instruction %s (%s)",
                    instr_tab[0], instr_tab[1]);
                exit(84);
            }
            get_args_type(new_op->type, new_op->args, args);
        }
    }
    new_op->next_op = *op_list;
    *op_list = new_op;
}
