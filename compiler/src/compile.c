/*
** EPITECH PROJECT, 2019
** compile.c
** File description:
** starts the compilation
*/

// #include "my.h"
#include "asm.h"

void compile(int fd)
{
    char *str;
    header_t *header = create_header(fd);
    label_t *label_list = create_label(NULL);

    // my_printf("{%s} -> {%s}\n", header->prog_name, header->comment);
    while ((str = get_next_instruction(fd)) != NULL) {
        // my_printf("instruction found: {\e[1m\e[34m%s\e[0m}\n", str);/*DEBUG*/
        parse_instruction(str, &label_list);
        free(str);
    }
    write_in_file(header, label_list);
    // free_all(header, label_list);
}
