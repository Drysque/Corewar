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
        if (my_strcmp(label_list->name, label)) {
            return label_list->offset;
        }
        label_list = label_list->next_label;
    }
    my_printf("\n\t\e[1m\e[31mUnknown label:\e[0m %s\n\n", label);
    exit(84);
    return 0;
}

void fill_needed_label(int fd, label_t *label_list)
{
    op_need_label_t *list = add_need_label(NULL, GET, 0, 0);
    off_t offset = 0;

    while (list) {
        // printf("{instruction at %d need %s} ", list->offset, list->label);
        // printf("{%s is at %d}\n", list->label, fetch_offset(label_list, list->label), list->size);
        offset = get_no_endian(fetch_offset(label_list, list->label) -
            list->begin_offset, list->size);
        // printf("SHIFT TO %d\n", list->offset + sizeof(header_t));
        lseek(fd, list->offset + sizeof(header_t), SEEK_SET);
        // printf("wrote %x at %d of size %d\n\n", get_no_endian(offset, list->size), lseek(fd, 0, SEEK_CUR), list->size);
        write(fd, &offset, list->size);
        list = list->next_op;
    }
}
