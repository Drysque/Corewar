/*
** EPITECH PROJECT, 2019
** compile.c
** File description:
** starts the compilation
*/

#include "asm.h"
#include "my.h"

void compile(int fd, char *new_file)
{
    char *str;
    header_t *header = my_calloc(sizeof(header_t));
    label_t *label_list = NULL;
    op_list_t *op_list = NULL;

    offset_pos(sizeof(header_t), ADD);
    while ((str = get_next_instruction(fd)) != NULL) {
        // my_printf("instruction found: {\e[1m\e[34m%s\e[0m}\n", str);/*DEBUG*/
        parse_instruction(str, &label_list, &op_list, header);
        free(str);
    }
    write_in_file(header, label_list, op_list, new_file);
}
