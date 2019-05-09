/*
** EPITECH PROJECT, 2019
** add_instruction.c
** File description:
** adds an instruction
*/

#include "asm.h"
#include "my.h"

// void get_args_type(op_list_t *op, char **instr_tab)
// {
//     for (int i = 0; instr_tab[i]; i++) {
//         if (instr_tab[i][0] == 'r') {
//             op->type[i] = 0b01;
//             op->true_type[i] = 0b01;
//             op->args[i] = my_getnbr(&instr_tab[i][1]);
//             offset_pos(1, ADD);
//             // my_printf("0x%x ", my_getnbr(&instr_tab[i][1]));
//         }
//         else if (instr_tab[i][0] == '%') {
//             op->type[i] = 0b10;
//             op->true_type[i] = (op->code == 0x09 || op->code == 0x0b ? 0b11 : 0b10);
//             offset_pos(4 - (op->code == 0x09 || op->code == 0x0b ? 2 : 0), ADD);
//             if (instr_tab[i][1] == LABEL_CHAR) {
//                 add_need_label(&instr_tab[i][2], ADD);
//             } else
//                 op->args[i] = my_getnbr(&instr_tab[i][1]);
//             // my_printf("0x00 0x00 0x00 0x%x ", my_getnbr(&instr_tab[i][1]));
//         }
//         else {
//             op->type[i] = 0b11;
//             op->true_type[i] = 0b11;
//             op->args[i] = my_getnbr(instr_tab[i]);
//             offset_pos(2, ADD);
//             // my_printf("0x00 0x%x ", my_getnbr(instr_tab[i]));
//         }
//     }
// }
//
// static void clean_arguments(char **instr_tab)
// {
//     int len;
//
//     for (int i = 0; instr_tab && instr_tab[i]; i++) {
//         len = my_strlen(instr_tab[i]);
//         if (instr_tab[i][len - 1] == SEPARATOR_CHAR)
//             instr_tab[i][len - 1] = '\0';
//     }
// }
//
// void add_instruction(char **instr_tab, op_list_t **op_list)
// {
//     op_list_t *new_op;
//
//     if (instr_tab[0] == NULL)
//         return;
//     new_op = my_calloc(sizeof(op_list_t));
//     clean_arguments(&instr_tab[1]);
//     for (int i = 0; op_tab[i].mnemonique != 0; i++) {
//         if (my_strcmp(op_tab[i].mnemonique, instr_tab[0])) {
//             new_op->code = op_tab[i].code;
//             offset_pos(1, ADD);
//
//             if (my_tablen((char const **) &instr_tab[1]) != op_tab[i].nbr_args) {
//                 my_printf("wrong number of arguments for instruction %s (%d)\n",
//                     instr_tab[0], my_tablen((char const **) &instr_tab[1]));
//                 exit(84);
//             }
//             get_args_type(new_op, &instr_tab[1]);
//             new_op->next_op = *op_list;
//             *op_list = new_op;
//             return;
//         }
//     }
//     my_printf("unknown instruction %s\n", instr_tab[0]);
//     exit(84);
// }
