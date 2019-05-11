/*
** EPITECH PROJECT, 2019
** write_in_file.c
** File description:
** write the program in a file.cor
*/

#include "my.h"
#include "asm.h"

static const char NO_CODING_BYTE[] = {0x01, 0x09, 0x0c, 0x0f, 0x0};

static void print_op(op_list_t *instruction_list, int fd)
{
    char type = 0;
    int swapped = 0;

    if (instruction_list == NULL)
        return;
    print_op(instruction_list->next_op, fd);
    // printf("wrote instruction %x at %d of size 1\n", instruction_list->code, lseek(fd, 0, SEEK_CUR));
    write(fd, &instruction_list->code, 1);
    printf("wrote instruction %x of size \e[1m\e[33m%d\e[0m\n", instruction_list->code, 1);
    for (int i = 0; i < MAX_ARGS_NUMBER; i++)
        type |= instruction_list->type[i] << (2 * (MAX_ARGS_NUMBER - 1 - i));
    if (is_one_of_them(instruction_list->code, NO_CODING_BYTE) == false) {
        printf("wrote type %x of size \e[1m\e[33m%d\e[0m\n", type, 1);
        write(fd, &type, 1);
    }
    for (int i = 0; i < MAX_ARGS_NUMBER && instruction_list->type[i]; i++) {
        switch (instruction_list->true_type[i]) {
        case 1: swapped = instruction_list->args[i];
            // printf("1 byte: not swapped: %x\n", swapped);
            printf("wrote %d of size \e[1m\e[33m%d\e[0m\n", get_no_endian(swapped, 1), 1);
            write(fd, &swapped, 1);
            break;
        case 2: swapped = get_no_endian(instruction_list->args[i], DIR_SIZE);
            // printf("4 bytes: swapped: %x\n", swapped);
            printf("wrote %d of size \e[1m\e[33m%d\e[0m\n", get_no_endian(swapped, DIR_SIZE), DIR_SIZE);
            write(fd, &swapped, DIR_SIZE);
            break;
        case 3: swapped = get_no_endian(instruction_list->args[i], IND_SIZE);
            // printf("2 bytes: swapped: %x\n", swapped);
            printf("wrote %d of size \e[1m\e[33m%d\e[0m\n", get_no_endian(swapped, IND_SIZE), IND_SIZE);
            write(fd, &swapped, IND_SIZE);
            break;
        default: break;
        }
    }
    printf("total bytes actually written: \e[1m\e[32m%d\e[0m\n", lseek(fd, 0, SEEK_CUR));
    printf("\n");

}

void write_in_file(header_t *header, label_t *label_list,
    op_list_t *op_list, char *new_file)
{
    int fd = open(new_file, O_TRUNC | O_CREAT | O_RDWR, 00666);

    if (fd < 0) {
        my_printf("\e[1m\e[31m%s: couldn't create file\e[0m\n", new_file);
        exit(84);
    }
    printf("total bytes actually written: \e[1m\e[32m%d\e[0m\n", lseek(fd, 0, SEEK_CUR));
    write(fd, header, sizeof(header_t));
    printf("printing header\ntotal bytes actually written: \e[1m\e[32m%d\e[0m\n\n", lseek(fd, 0, SEEK_CUR));
    print_op(op_list, fd);

    fill_needed_label(fd, label_list);
    header->magic = get_no_endian(COREWAR_EXEC_MAGIC, 4);
    printf("total written: %d\n", lseek(fd, 0, SEEK_END));
    header->prog_size = get_no_endian(offset_pos(0, GET), 4);
    lseek(fd, 0, SEEK_SET);
    write(fd, header, sizeof(header_t));
    close(fd);
    // printf("name: {%s}, comment {%s}\n", header->prog_name, header->comment);
}
