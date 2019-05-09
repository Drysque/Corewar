/*
** EPITECH PROJECT, 2019
** fill_needed_label.c
** File description:
** -
*/

#include "asm.h"
#include "my.h"

static off_t fetch_offset(label_t *label_list, char *label, int size)
{
    while (label_list) {
        if (my_strcmp(label_list->name, label))
            return get_no_endian(label_list->offset, size);
        label_list = label_list->next_label;
    }
    my_printf("unknown label: %s", label);
    exit(84);
    return 0;
}

void fill_needed_label(int fd, label_t *label_list)
{
    op_need_label_t *list = add_need_label(NULL, GET, 0);
    off_t offset = 0;

    while (list) {
        my_printf("{instruction at %d need %s} ", list->offset, list->label);
        my_printf("{%s is at %d}\n", list->label, fetch_offset(label_list, list->label, list->size));
        offset = fetch_offset(label_list, list->label, list->size);
        lseek(fd, list->offset + sizeof(header_t), SEEK_SET);
        write(fd, &offset, list->size);
        list = list->next_op;
    }
}
