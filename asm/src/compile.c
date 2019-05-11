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

    // printf("\ntotal bytes theorically written: \e[1m\e[32m%d\e[0m (%d)\n", offset_pos(0, GET) + sizeof(header_t), offset_pos(0, GET));
    get_name_or_comment(fd, header);
    while ((str = get_next_instruction(fd)) != NULL) {
        // printf("\ninstruction found: {\e[1m\e[34m%s\e[0m}\n", str);
        parse_instruction(str, &label_list, &op_list);
        free(str);
    }
    // printf("\n------------BEGINNING WRITING-----------\n\n");
    write_in_file(header, label_list, op_list, new_file);
}
