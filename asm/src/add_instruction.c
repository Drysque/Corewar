/*
** EPITECH PROJECT, 2019
** add_instruction.c
** File description:
** adds an instruction
*/

#include "asm.h"
#include "my.h"

static const char NO_CODING_BYTE[] = {0x01, 0x09, 0x0c, 0x0f, 0x0};
static const char NO_DIRECT_SIZE[] = {0x05, 0x09, 0x0b, 0x0c, 0x0};

static void get_direct_indirect(op_list_t *op, char **instr_tab, int i)
{
    if (instr_tab[i][0] == DIRECT_CHAR) {
        op->type[i] = 0b10;
        op->true_type[i] = is_one_of_them(op->code,NO_DIRECT_SIZE)
            ? 0b11 : 0b10;
        if (instr_tab[i][1] == LABEL_CHAR)
            add_need_label(&instr_tab[i][2], ADD,
                op->true_type[i], op->begin_offset);
        else
            op->args[i] = my_getnbr(&instr_tab[i][1]);
        offset_pos(op->true_type[i] == 0b10 ? DIR_SIZE : IND_SIZE, ADD); // printf("added offset of %d for dir/indir\n", op->true_type[i] == 2 ? 4 : 2);
    } else {
        op->type[i] = 0b11;
        op->true_type[i] = 0b11;
        op->args[i] = my_getnbr(instr_tab[i]);
        offset_pos(IND_SIZE, ADD);
        // printf("added offset of 2 for indirect\n");
    }
}

static void get_args_type(op_list_t *op, char **instr_tab)
{
    for (int i = 0; instr_tab[i]; i++) {
        if (instr_tab[i][0] == 'r') {
            op->type[i] = 0b01;
            op->true_type[i] = 0b01;
            op->args[i] = my_getnbr(&instr_tab[i][1]);
            offset_pos(1, ADD);// printf("added offset of 1 for register\n");
        } else
           get_direct_indirect(op, instr_tab, i);
    }
}

static void fill_op(op_list_t *new_op, char **instr_tab, op_t *op)
{
    new_op->code = op->code;
    offset_pos(1, ADD);
    if (is_one_of_them(op->code, NO_CODING_BYTE) == false)
        offset_pos(1, ADD);
    if (my_tablen((char const **)&instr_tab[1]) != op->nbr_args) {
        my_printf("\n\t\e[1m\e[31mwrong number of arguments:\e[0m %s "
            "(\e[5m%d\e[0m expected %d)\n\n", instr_tab[0],
            my_tablen((char const **)&instr_tab[1]), op->nbr_args);
        exit(84);
    }
    get_args_type(new_op, &instr_tab[1]);
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
    my_printf("\n\t\e[1m\e[31munknown instruction:\e[0m %s\n\n", instr_tab[0]);
    exit(84);
}
