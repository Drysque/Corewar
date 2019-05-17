/*
** EPITECH PROJECT, 2019
** add_instruction.c
** File description:
** adds an instruction
*/

#include "asm.h"
#include "my.h"

static const char NO_CODING_BYTE[] = {0x01, 0x09, 0x0c, 0x0f, 0x0};
static const char NO_DIRECT_SIZE[] = {0x05, 0x09, 0x0a, 0x0b, 0x0c, 0x0f, 0x0};

static void fill_op(op_list_t *new_op, char **instr_tab, op_t *op)
{
    new_op->code = op->code;
    offset_pos(1, ADD);
    if (is_one_of_them(op->code, NO_CODING_BYTE) == false)
        offset_pos(1, ADD);
    if (my_tablen((char const **)&instr_tab[1]) != op->nbr_args) {
        my_printf("\n\tline %d: \e[1m\e[31mWrong number of arguments:\e[0m %s "
            "(\e[5m%d\e[0m, expected %d)\n\n", line_counter(GET), instr_tab[0],
            my_tablen((char const **)&instr_tab[1]), op->nbr_args);
        exit(84);
    }
    get_args_type(new_op, &instr_tab[1], op);
}

void add_instruction(char **instr_tab, op_list_t **op_list)
{
    op_list_t *new_op;

    if (instr_tab[0] == NULL)
        return;
    new_op = my_calloc(sizeof(op_list_t));
    new_op->begin_offset = offset_pos(0, GET);
    for (int i = 0; op_tab[i].mnemonique != 0; i++) {
        if (my_strcmp(op_tab[i].mnemonique, instr_tab[0])) {
            fill_op(new_op, instr_tab, &op_tab[i]);
            new_op->next_op = *op_list;
            *op_list = new_op;
            // printf("total bytes theorically written: \e[1m\e[32m%d\e[0m (%d)\n", offset_pos(0, GET) + sizeof(header_t), offset_pos(0, GET));
            return;
        }
    }
    my_error_str("Unknown instruction:\e[0m %s", instr_tab[0]);
}
