/*
** EPITECH PROJECT, 2019
** get_next_instruction.c
** File description:
** gets the next instruction
*/

#include "asm.h"
#include "my.h"
#include "op.h"

// static char *clean_instruction(char *instruction)
// {
//     char *save = instruction;
//
//     instruction = my_strdup(&instruction[1]);
//     free(save);
//     return instruction;
// }

char *get_next_instruction(int fd)
{
    char *instruction = get_next_line(fd);

    if (instruction == NULL)
        return NULL;
    if (instruction[0] == COMMENT_CHAR || my_strlen(instruction) <= 0) {
        free(instruction);
        return get_next_instruction(fd);
    }
    // if (instruction[0] == '\t')
    //     instruction = clean_instruction(instruction);
    return instruction;
}
