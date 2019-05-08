/*
** EPITECH PROJECT, 2019
** add_instruction.c
** File description:
** adds an instruction
*/

#include "asm.h"
#include "my.h"

void get_args_type(char *type, int *args, char **instr_tab)
{
    for (int i = 0; instr_tab[i]; i++) {
        if (instr_tab[i][0] == 'r') {
            type[i] = 0b01;
            // my_printf("0x%x ", my_getnbr(&instr_tab[i][1]));
            args[i] = my_str_to_char(&instr_tab[i][1]);
            offset_pos(1, ADD);
        }
        else if (instr_tab[i][0] == '%') {
            // my_printf("0x00 0x00 0x00 0x%x ", my_getnbr(&instr_tab[i][1]));
            type[i] = 0b10;
            if (instr_tab[i][1] == LABEL_CHAR) {
                args[i] = 0;
                add_need_label(&instr_tab[i][2], ADD);
                offset_pos(1, ADD);
            } else {
                args[i] = my_getnbr(&instr_tab[i][1]);
                offset_pos(1, ADD);
            }
        }
        else {
            type[i] = 0b11;
            args[i] = my_str_to_int16(instr_tab[i]);
            // my_printf("0x00 0x%x ", my_getnbr(instr_tab[i]));
        }
    }
}

static void clean_arguments(char **instr_tab)
{
    int len;

    for (int i = 0; instr_tab && instr_tab[i]; i++) {
        len = my_strlen(instr_tab[i]);
        if (instr_tab[i][len - 1] == SEPARATOR_CHAR)
            instr_tab[i][len - 1] = '\0';
    }
}

void add_instruction(char **instr_tab, op_list_t **op_list)
{
    op_list_t *new_op;

    if (instr_tab[0] == NULL)
        return;
    new_op = my_calloc(sizeof(op_list_t));
    clean_arguments(&instr_tab[1]);
    for (int i = 0; op_tab[i].mnemonique != 0; i++) {
        if (my_strcmp(op_tab[i].mnemonique, instr_tab[0])) {
            new_op->code = op_tab[i].code;
            offset_pos(1, ADD);

            if (my_tablen((char const **) &instr_tab[1]) != op_tab[i].nbr_args) {
                my_printf("wrong number of arguments for instruction %s (%d)\n",
                    instr_tab[0], my_tablen((char const **) &instr_tab[1]));
                exit(84);
            }
            get_args_type(new_op->type, new_op->args, &instr_tab[1]);
            new_op->next_op = *op_list;
            *op_list = new_op;
            return;
        }
    }
    my_printf("unknown instruction %s\n", instr_tab[0]);
    exit(84);
}
