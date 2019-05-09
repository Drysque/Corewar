/*
** EPITECH PROJECT, 2019
** offset_manage.c
** File description:
** registers written bytes
*/

#include "asm.h"
#include "my.h"

op_need_label_t *add_need_label(char *name, int status, int size)
{
    static op_need_label_t *need_label = NULL;
    op_need_label_t *new_need_label = NULL;

    if (status == ADD) {
        new_need_label = my_calloc(sizeof(op_need_label_t));
        new_need_label->offset = offset_pos(0, GET);
        new_need_label->label = name;
        new_need_label->size = size;
        new_need_label->next_op = need_label;
        need_label = new_need_label;
        my_printf("instruction at %d needs %s\n", new_need_label->offset, name);
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
