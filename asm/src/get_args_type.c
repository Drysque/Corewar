/*
** EPITECH PROJECT, 2019
** get_args_type.c
** File description:
** gets the arguments types and values
*/

#include "asm.h"
#include "my.h"

static const char NO_DIRECT_SIZE[] = {0x05, 0x09, 0x0a, 0x0b, 0x0c, 0x0f, 0x0};

static void set_register(char **instr_tab, op_list_t *new_op, op_t *op, int i)
{
    new_op->type[i] = 0b01;
    new_op->true_type[i] = 0b01;
    if ((op->type[i] & T_REG) == 0) {
        my_printf("\n\t\e[1m\e[31mInvalid argument type for instruction:\e[0m "
            "\e[5m%s\e[0m register value not expected\n\n", op->mnemonique);
        exit(84);
    }
    new_op->args[i] = my_getnbr(&instr_tab[i][1]);
    if (new_op->args[i] <= 0 || new_op->args[i] > REG_NUMBER) {
        my_printf("\n\t\e[1m\e[31mInvalid register number:\e[0m "
            "\e[5m%d\e[0m is negative or too high\n\n", new_op->args[i]);
        exit(84);
    }
    offset_pos(1, ADD);
}

static void set_direct(char **instr_tab, op_list_t *new_op, op_t *op, int i)
{
    new_op->type[i] = 0b10;
    new_op->true_type[i] = is_one_of_them(new_op->code, NO_DIRECT_SIZE)
        ? 0b11 : 0b10;
    if ((op->type[i] & T_DIR) == 0) {
        my_printf("\n\t\e[1m\e[31mInvalid argument type for instruction:\e[0m "
            "\e[5m%s\e[0m direct value not expected\n\n", op->mnemonique);
        exit(84);
    }
    if (instr_tab[i][1] == LABEL_CHAR)
        add_need_label(&instr_tab[i][2], ADD, new_op->true_type[i],
            new_op->begin_offset);
    else {
        if (my_strlen(&instr_tab[i][1]) <= 0)
            my_error("\n\t\e[1m\e[31mExpected value after direct\e[0m\n\n");
        new_op->args[i] = my_getnbr(&instr_tab[i][1]);
    }
    offset_pos(new_op->true_type[i] == 0b10 ? DIR_SIZE : IND_SIZE, ADD);
}

static void set_indirect(char **instr_tab, op_list_t *new_op, op_t *op, int i)
{
    new_op->type[i] = 0b11;
    new_op->true_type[i] = 0b11;
    if ((op->type[i] & T_IND) == 0) {
        my_printf("\n\t\e[1m\e[31mInvalid argument type for instruction:\e[0m "
            "\e[5m%s\e[0m indirect value not expected\n\n", op->mnemonique);
        exit(84);
    }
    if (instr_tab[i][0] == LABEL_CHAR)
        add_need_label(&instr_tab[i][1], ADD, 0b11, new_op->begin_offset);
    else
        new_op->args[i] = my_getnbr(&instr_tab[i][0]);
    offset_pos(IND_SIZE, ADD);
}

// printf("added offset of 1 for register\n");
// printf("added offset of %d for dir/indir\n", new_op->true_type[i] == 2 ? 4 : 2);
// printf("added offset of 2 for indirect\n");
void get_args_type(op_list_t *new_op, char **instr_tab, op_t *op)
{
    for (int i = 0; instr_tab[i]; i++) {
        if (instr_tab[i][0] == 'r')
            set_register(instr_tab, new_op, op, i);
        else if (instr_tab[i][0] == DIRECT_CHAR)
            set_direct(instr_tab, new_op, op, i);
        else
            set_indirect(instr_tab, new_op, op, i);
    }
}
