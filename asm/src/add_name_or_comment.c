/*
** EPITECH PROJECT, 2019
** add_name_or_comment.c
** File description:
** adds a name or a comment
*/

#include "asm.h"
#include "my.h"

static void remove_quotes(char *instruct, int *index)
{
    if (instruct[*index] == '\"') {
        (*index)++;
        for (int len = my_strlen(instruct) - 1; len > 0; len--)
            if (instruct[len] == '\"') {
                instruct[len] = 0;
                break;
            }
    }
}

bool add_name_or_comment(char *instruct, header_t *header)
{
    int index = 0;
    bool name = false;
    int len[2] = {my_strlen(NAME_CMD_STRING), my_strlen(COMMENT_CMD_STRING)};

    for (; instruct[index] && is_one_of_them(instruct[index], " \t"); index++);
    if (instruct[index] == '\0')
        return false;
    if (my_strncmp(&instruct[index], NAME_CMD_STRING, len[0])) {
        index += len[0];
        name = true;
    } else if (my_strncmp(&instruct[index], COMMENT_CMD_STRING, len[1]))
        index += len[1];
    else
        return false;
    for (; instruct[index] && is_one_of_them(instruct[index], " \t"); index++);
    if (instruct[index] == '\0')
        return false;
    remove_quotes(instruct, &index);
    my_strcpy(name ? header->prog_name : header->comment, &instruct[index]);
    return true;
}
