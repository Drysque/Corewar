/*
** EPITECH PROJECT, 2018
** my_get_next_line.c
** File description:
** GNL project
*/

#include <stdlib.h>
#include <unistd.h>

int my_strlen(char const *str);
char *my_strcat(char *buffer, char *str);

static const int READ_SIZE = 100;

static int eol_index(char *str)
{
    for (int i = 0; str && str[i]; i++)
        if (str[i] == '\n')
            return (i);
    return (-1);
}

static char *save_after_eol(char *buffer)
{
    int index = 0;

    for (index = 0; buffer[index] != '\n' && buffer[index]; index++);
    return (&buffer[++index]);
}

char *get_next_line(int fd)
{
    static char *save = NULL;
    char *buffer = save;
    char *readstr = NULL;
    int rd;
    int i = 0;

    while (1) {
        if (my_strlen(buffer) > 0 && (i = eol_index(buffer)) >= 0) {
            save = save_after_eol(buffer);
            buffer[i] = '\0';
            return (my_strcat(buffer, "\0"));
        }
        else {
            if (!(readstr = malloc(sizeof(char) * READ_SIZE + 1)) || fd < 0
                || (rd = read(fd, readstr, READ_SIZE)) < 1)
                return NULL;
            readstr[rd] = 0;
            buffer = my_strcat(buffer, readstr);
        }
    }
}
