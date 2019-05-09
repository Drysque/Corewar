/*
** EPITECH PROJECT, 2019
** fill_needed_label.c
** File description:
** -
*/

#include "asm.h"
#include "my.h"

static off_t fetch_offset(label_t *label_list, char *label)
{
    while (label_list) {
        if (my_strcmp(label_list->name, label))
            return label_list->offset;
        label_list = label_list->next_label;
    }
    my_printf("unknown label: %s", label);
    exit(84);
    return 0;
}

void fill_needed_label(int fd, label_t *label_list)
{
    op_need_label_t *list = add_need_label(NULL, GET);
    off_t offset = 0;

    while (list) {
        my_printf("{instruction at %d need %s} ", list->offset, list->label);
        my_printf("{%s is at %d}\n", list->label, fetch_offset(label_list, list->label));
        offset = fetch_offset(label_list, list->label);
        lseek(fd, list->offset, SEEK_SET);
        write(fd, &offset, sizeof(int));
        list = list->next_op;
    }
}
