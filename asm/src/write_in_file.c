/*
** EPITECH PROJECT, 2019
** write_in_file.c
** File description:
** write the program in a file.cor
*/

#include "my.h"
#include "asm.h"

static const char NO_CODING_BYTE[] = {0x01, 0x09, 0x0c, 0x0f, 0x0};

static void write_arguments(int fd, op_list_t *instruction_list)
{
    int swapped = 0;

    for (int i = 0; i < MAX_ARGS_NUMBER && instruction_list->type[i]; i++) {
        switch (instruction_list->true_type[i]) {
        case 1: swapped = instruction_list->args[i];
            write(fd, &swapped, 1);
            break;
        case 2: swapped = get_no_endian(instruction_list->args[i], DIR_SIZE);
            write(fd, &swapped, DIR_SIZE);
            break;
        case 3: swapped = get_no_endian(instruction_list->args[i], IND_SIZE);
            write(fd, &swapped, IND_SIZE);
            break;
        default: break;
        }
    }
}

static void print_op(op_list_t *instruction_list, int fd)
{
    char type = 0;

    if (instruction_list == NULL)
        return;
    print_op(instruction_list->next_op, fd);
    write(fd, &instruction_list->code, 1);
    for (int i = 0; i < MAX_ARGS_NUMBER; i++)
        type |= instruction_list->type[i] << (2 * (MAX_ARGS_NUMBER - 1 - i));
    if (is_one_of_them(instruction_list->code, NO_CODING_BYTE) == false)
        write(fd, &type, 1);
    write_arguments(fd, instruction_list);
}

void write_in_file(header_t *header, label_t *label_list,
    op_list_t *op_list, char *new_file)
{
    int fd = open(new_file, O_TRUNC | O_CREAT | O_RDWR, 00666);

    if (fd < 0)
        my_error_str("%s: couldn't create file", new_file);
    write(fd, header, sizeof(header_t));
    print_op(op_list, fd);
    fill_needed_label(fd, label_list);
    header->magic = get_no_endian(COREWAR_EXEC_MAGIC, 4);
    header->prog_size = get_no_endian(offset_pos(0, GET), 4);
    lseek(fd, 0, SEEK_SET);
    write(fd, header, sizeof(header_t));
    close(fd);
}
