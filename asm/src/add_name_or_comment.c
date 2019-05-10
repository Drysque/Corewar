/*
** EPITECH PROJECT, 2019
** add_name_or_comment.c
** File description:
** adds a name or a comment
*/

#include "asm.h"
#include "my.h"

bool add_name_or_comment(char *instruction, header_t *header)
{
    int index = 0;
    int i = 0;

    for (; instruction[index] != '\0' && (instruction[index] == ' ' || instruction[index] == '\t'); index += 1);
    if (instruction[index] == '\0')
        return false;
    if (my_strncmp(&instruction[index], NAME_CMD_STRING, my_strlen(NAME_CMD_STRING)))
        index += my_strlen(NAME_CMD_STRING);
    else if (my_strncmp(&instruction[index], COMMENT_CMD_STRING, my_strlen(COMMENT_CMD_STRING))) {
        index += my_strlen(COMMENT_CMD_STRING);
        i = 1;
    } else
        return false;
    for (; instruction[index] != '\0' &&
    (instruction[index] == ' ' || instruction[index] == '\t'); index += 1);
    if (instruction[index] == '\0')
        return false;
    if (instruction[index] == '\"') {
        index += 1;
        for (int len = my_strlen(instruction) - 1; len > 0; len--)
            if (instruction[len] == '\"') {
                instruction[len] = 0;
                break;
            }
    }
    if (i == 0)
        my_strcpy(header->prog_name, &instruction[index]);
    else
        my_strcpy(header->comment, &instruction[index]);
    return true;
}
