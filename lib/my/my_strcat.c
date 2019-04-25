/*
** EPITECH PROJECT, 2018
** my_strcat.c
** File description:
** concats two stings into a new one
*/

#include <stdlib.h>
int my_strlen(char const *str);

char *my_strcat(char *buffer, char *str)
{
    int len = my_strlen(buffer) + my_strlen(str);
    char *catstr = malloc(sizeof(char) * len + 1);
    int index = 0;

    if (buffer == NULL)
        return str;
    for (int i = 0; buffer[i]; i++)
        catstr[index++] = buffer[i];
    for (int i = 0; str[i]; i++)
        catstr[index++] = str[i];
    catstr[index] = '\0';
    return (catstr);
}
