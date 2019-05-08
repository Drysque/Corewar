/*
** EPITECH PROJECT, 2019
** my_write.c
** File description:
** registers written bytes
*/

#include "asm.h"
#include "my.h"

///!\ PAS BESOIN, LSEEK DONNE L'ENDROIT OU ON EST DEPUIS LE DEBUT

op_need_label_t *add_need_label(char *name, int status)
{
    static op_need_label_t *need_label = NULL;
    op_need_label_t *new_need_label = NULL;

    if (status == ADD) {
        new_need_label = my_calloc(sizeof(op_need_label_t));
        new_need_label->offset = offset_pos(0, GET);
        new_need_label->label = name;
        new_need_label->next_op = need_label;
        need_label = new_need_label;
    }
    return need_label;
}

off_t offset_pos(ssize_t written, int status)
{
    static off_t offset = 0;

    if (status == ADD)
        offset += written;
    if (status == SUB)
        offset -= written;
    return offset;
}

// void my_write(int fd, void *buf, size_t n)
// {
//     ssize_t written = write(fd, buf, n);
//
//     if (write == -1) {
//         my_printf("syscall error: write\n");
//         exit(84);
//     }
//     offset_pos(written, ADD);
// }
