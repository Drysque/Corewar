/*
** EPITECH PROJECT, 2019
** compile.c
** File description:
** starts the compilation
*/

#include "asm.h"
#include "my.h"

// static void free_op(op_list_t *instruction_list)
// {
//     if (instruction_list == NULL)
//         return;
//     free_op(instruction_list->next_op);
//     free(instruction_list);
// }
//
// static void free_label(label_t *label_list)
// {
//     if (label_list == NULL)
//         return;
//     free_label(label_list->next_label);
//     free_op(label_list->instruction_list);
//     free(label_list);
// }
//
// void free_all(header_t *header, label_t *label_list)
// {
//     free(header);
//     free_label(label_list);
// }

void compile(int fd, char *new_file)
{
    char *str;
    header_t *header = my_calloc(sizeof(header_t));
    label_t *label_list = NULL;
    op_list_t *op_list = NULL;

    // my_printf("{%s} -> {%s}\n", header->prog_name, header->comment);
    offset_pos(sizeof(header_t), ADD);
    while ((str = get_next_instruction(fd)) != NULL) {
        // my_printf("instruction found: {\e[1m\e[34m%s\e[0m}\n", str);/*DEBUG*/
        parse_instruction(str, &label_list, &op_list, header);
        free(str);
    }
    write_in_file(header, label_list, op_list, new_file);
    // free_all(header, label_list);
}
