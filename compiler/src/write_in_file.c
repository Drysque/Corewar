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
    char type = 0;

    if (instruction_list == NULL)
        return;
    print_op(instruction_list->next_op, fd);
    write(fd, &instruction_list->code, sizeof(char));
    for (int i = 0; i < MAX_ARGS_NUMBER; i++)
        type |= instruction_list->type[i] << (2 * (MAX_ARGS_NUMBER - 1 - i));
    write(fd, &type, 1);
    for (int i = 0; i < MAX_ARGS_NUMBER && instruction_list->type[i]; i++) {
        switch (instruction_list->type[i]) {
        case 1: write(fd, &instruction_list->args[i], 1);
            break;
        case 2: write(fd, "\0\0\0", 3);
            write(fd, &instruction_list->args[i], 1);
            printf("%d\n", instruction_list->args[i]);
            break;
        case 3: write(fd, "\0", 1);
            write(fd, &instruction_list->args[i], 1);
            break;
        default: break;
        }
    }
    // /*DEBUG*/my_printf("\t%s", instruction_list->mnemonique);
    // /*DEBUG*/my_printf("\t(\e[1m\e[32m0x0%x\e[0m)\n", instruction_list->code);
    // my_printf("\tcycles: %d\n", instruction_list->nbr_cycles);
    // my_printf("\tcomment: %s\n", instruction_list->comment);
    // write(fd, instruction_list->type, MAX_ARGS_NUMBER);
    // /*DEBUG*/my_printf("\targ types: \e[1m\e[32m", instruction_list->type);
    // /*DEBUG*/for (int i = 0; i < 4; i++)
    // /*DEBUG*/    my_printf("%d", instruction_list->type[i]);
    // /*DEBUG*/my_printf("\e[0m\n");
}

static void print_label(label_t *label_list, int fd)
{
    if (label_list == NULL)
        return;
    print_label(label_list->next_label, fd);
    print_op(label_list->instruction_list, fd);
    // /*DEBUG*/if (label_list->instruction_list != NULL)
    // /*DEBUG*/    my_printf("%s:\n", label_list->name);
}

// static void print_header(header_t *header, int fd)
// {
//     // /*DEBUG*/my_printf("header: \n\t%x\n\t{%s}, {%s}\n\n", header->magic, header->prog_name, header->comment);
// }

void write_in_file(header_t *header, label_t *label_list, char *new_file)
{
    int fd = open(new_file, O_TRUNC | O_CREAT | O_RDWR, 00666);

    if (fd < 0) {
        my_printf("\e[1m\e[31m%s: couldn't create file\e[0m\n", new_file);
        exit(84);
    }
    write(fd, header, sizeof(header_t));
    print_label(label_list, fd);
    close(fd);
}
