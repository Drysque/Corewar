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
    my_error_str("Unknown label:\e[0m %s", label);
    return 0;
}

void fill_needed_label(int fd, label_t *label_list)
{
    op_need_label_t *list = add_need_label(NULL, GET, 0, 0);
    off_t offset = 0;

    while (list) {
        offset = get_no_endian(fetch_offset(label_list, list->label) -
            list->begin_offset, list->size);
        lseek(fd, list->offset + sizeof(header_t), SEEK_SET);
        write(fd, &offset, list->size);
        list = list->next_op;
    }
}
