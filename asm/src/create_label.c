/*
** EPITECH PROJECT, 2019
** create_label.c
** File description:
** creates a header
*/

#include "asm.h"
#include "my.h"

label_t *create_label(char *name)
{
    label_t *label = my_calloc(sizeof(label_t));

    label->name = name;
    // label->next_label = NULL;(calloc)
    // label->instruction_list = NULL;(calloc)y
    return label;
}
