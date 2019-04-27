/*
** EPITECH PROJECT, 2019
** create_label.c
** File description:
** creates a header
*/

#include "asm.h"

label_t *create_label(char *name)
{
    label_t *label = malloc(sizeof(label_t));

    label->name = name;
    label->next_label = NULL;
    label->instruction_list = NULL;
    return label;
}
