/*
** EPITECH PROJECT, 2019
** write_in_file.c
** File description:
** write the program in a file.cor
*/

#include "my.h"
#include "asm.h"

static void print_op(op_list_t *instruction_list, int fd)
{
    if (instruction_list == NULL)
        return;
    print_op(instruction_list->next_op, fd);
    my_printf("\t%s\n", instruction_list->op->mnemonique);
}

static void print_label(label_t *label_list, int fd)
{
    if (label_list == NULL)
        return;
    print_label(label_list->next_label, fd);
    if (label_list->instruction_list != NULL)
        my_printf("%s:\n", label_list->name);
    print_op(label_list->instruction_list, fd);
}

static void print_header(header_t *header, int fd)
{
    my_printf("header: \n\t%x\n\t{%s}, {%s}\n\n", header->magic, header->prog_name, header->comment);
}

void write_in_file(header_t *header, label_t *label_list, char *new_file)
{
    int fd = 4;// open(new_file);
    print_header(header, fd);
    print_label(label_list, fd);
    // close(fd);
}
