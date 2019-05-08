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
    //if(instruction code == zjmp ou else, ecrire meme taille)offset_pos(3, SUB);
    for (int i = 0; i < MAX_ARGS_NUMBER && instruction_list->type[i]; i++) {
        switch (instruction_list->type[i]) {
        case 1:
            write(fd, &instruction_list->args[i], 1);
            //printf("arg: register 0x%d\n", *((char *)instruction_list->args[i]));
            break;
        case 2: //write(fd, "\0\0\0", 3);
            write(fd, &instruction_list->args[i], 4);
            //printf("arg: indirect 0x0 0x0 0x0 0x%x\n", *((int *)instruction_list->args[i]));
            break;
        case 3: //write(fd, "\0", 1);
            write(fd, &instruction_list->args[i], 2);
            //printf("arg: direct 0x0 0x%d\n", *((u_int16_t *)instruction_list->args[i]));
            break;
        default: break;
        }
    }
}

void write_in_file(header_t *header, label_t *label_list,
    op_list_t *op_list, char *new_file)
{
    int fd = open(new_file, O_TRUNC | O_CREAT | O_RDWR, 00666);

    if (fd < 0) {
        my_printf("\e[1m\e[31m%s: couldn't create file\e[0m\n", new_file);
        exit(84);
    }
    write(fd, header, sizeof(header_t));
    print_op(op_list, fd);

    //FINAL
    fill_needed_label(fd, label_list);
    header->magic = COREWAR_EXEC_MAGIC;
    header->prog_size = offset_pos(0, GET);
    lseek(fd, 0, SEEK_SET);//GOBACK
    write(fd, header, sizeof(header_t));
    close(fd);
}
