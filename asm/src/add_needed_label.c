/*
** EPITECH PROJECT, 2019
** add_needed_label.c
** File description:
** adds instruction to the ones that need a label
*/

#include "asm.h"
#include "my.h"

op_need_label_t *add_need_label(char *name, int status,
    int size, off_t begin_offset)
{
    static op_need_label_t *need_label = NULL;
    op_need_label_t *new_need_label = NULL;

    if (status == ADD) {
        new_need_label = my_calloc(sizeof(op_need_label_t));
        new_need_label->label = my_strdup(name);
        new_need_label->size = (size == 0b10 ? DIR_SIZE : IND_SIZE);
        new_need_label->offset = offset_pos(0, GET);
        new_need_label->begin_offset = begin_offset;
        new_need_label->next_op = need_label;
        need_label = new_need_label;
    }
    return need_label;
}
