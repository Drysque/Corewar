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
    bool name = false;

    for (; instruction[index] != '\0' && is_one_of_them(instruction[index], " \t"); index++);
    if (instruction[index] == '\0')
        return false;
    if (my_strncmp(&instruction[index], NAME_CMD_STRING, my_strlen(NAME_CMD_STRING))) {
        index += my_strlen(NAME_CMD_STRING);
        name = true;
    } else if (my_strncmp(&instruction[index], COMMENT_CMD_STRING, my_strlen(COMMENT_CMD_STRING)))
        index += my_strlen(COMMENT_CMD_STRING);
    else
        return false;
    for (; instruction[index] && is_one_of_them(instruction[index], " \t") ; index++);
    if (instruction[index] == '\0')
        return false;
    if (instruction[index] == '\"') {
        index++;
        for (int len = my_strlen(instruction) - 1; len > 0; len--)
            if (instruction[len] == '\"') {
                instruction[len] = 0;
                break;
            }
    }
    if (name)
        my_strcpy(header->prog_name, &instruction[index]);
    else
        my_strcpy(header->comment, &instruction[index]);
    // my_strcpy(name ? header->prog_name : header->comment, &instruction[index]);
    return true;
}
