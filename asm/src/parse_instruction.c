/*
** EPITECH PROJECT, 2019
** parse_instruction.c
** File description:
** parses the instruction
*/

#include "my.h"
#include "asm.h"

static void add_label(char *label_name, label_t **label_list)
{
    label_t *new_label = my_calloc(sizeof(label_t));

    new_label->name = label_name;
    new_label->offset = offset_pos(0, GET);
    new_label->next_label = *label_list;
    *label_list = new_label;
}

bool add_name_or_comment(char *instruction, header_t *header)
{
    if (my_strncmp(instruction, NAME_CMD_STRING, my_strlen(NAME_CMD_STRING))) {
        instruction[my_strlen(instruction) - 1] = 0;
        my_strcpy(header->prog_name, &instruction[my_strlen(NAME_CMD_STRING) + 2]);
    } else if (my_strncmp(instruction, COMMENT_CMD_STRING, my_strlen(COMMENT_CMD_STRING))) {
        instruction[my_strlen(instruction) - 1] = 0;
        my_strcpy(header->comment, &instruction[my_strlen(COMMENT_CMD_STRING) + 2]);
    } else
        return false;
    return true;
}

void parse_instruction(char *instruction, label_t **label_list,
    op_list_t **op_list, header_t *header)
{
    char **tab = my_str_delim_array(instruction, " \t");

    if (tab == NULL) {
        my_printf("instruction failure: {%s}\n", instruction);
        exit(84);
    }
    if (add_name_or_comment(instruction, header));
    else if (tab[0][my_strlen(tab[0]) - 1] == LABEL_CHAR) {
        tab[0][my_strlen(tab[0]) - 1] = 0;
        add_label(tab[0], label_list);
        add_instruction(&tab[1], op_list);
    }
    else {
        add_instruction(tab, op_list);
    }
}
