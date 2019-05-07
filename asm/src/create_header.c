/*
** EPITECH PROJECT, 2019
** create_header.c
** File description:
** creates the header
*/

#include "my.h"
#include "asm.h"
#include "op.h"

header_t *create_header(int fd)
{
    header_t *header = my_calloc(sizeof(header_t));
    char *str;

    header->magic = COREWAR_EXEC_MAGIC;
    // header->prog_size = 0;(calloc)
    str = get_next_instruction(fd);
    str[my_strlen(str) - 1] = 0;
    my_strcpy(header->prog_name, &str[my_strlen(NAME_CMD_STRING) + 2]);
    free(str);
    str = get_next_instruction(fd);
    str[my_strlen(str) - 1] = 0;
    my_strcpy(header->comment, &str[my_strlen(COMMENT_CMD_STRING) + 2]);
    free(str);
    return header;
}
