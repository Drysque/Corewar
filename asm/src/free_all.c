/*
** EPITECH PROJECT, 2019
** free_all.c
** File description:
** -
*/

#include "asm.h"

static void free_op_list(op_list_t *op_list)
{
    if (op_list == NULL)
        return;
    free_op_list(op_list->next_op);
    free(op_list);
}

static void free_label_list(label_t *label_list)
{
    if (label_list == NULL)
        return;
    free_label_list(label_list->next_label);
    free(label_list->name);
    free(label_list);
}

void free_all(header_t *header, label_t *label_list, op_list_t *op_list)
{
    free(header);
    free_op_list(op_list);
    free_label_list(label_list);
}
