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
    my_printf("\t%s", instruction_list->op->mnemonique);
    my_printf("\t(\e[1m\e[32m0x0%x\e[0m)\n", instruction_list->op->code);
    // my_printf("\tcycles: %d\n", instruction_list->op->nbr_cycles);
    // my_printf("\tcomment: %s\n", instruction_list->op->comment);
    my_printf("\targ types: \e[1m\e[32m", instruction_list->op->type);
    for (int i = 0; i < 4; i++)
        my_printf("%d", instruction_list->op->type[i]);
    my_printf("\e[0m\n");

    // my_printf("\t%d args\n", instruction_list->op->nbr_args);
    // my_printf("\n");
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
