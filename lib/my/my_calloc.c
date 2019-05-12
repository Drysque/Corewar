/*
** EPITECH PROJECT, 2019
** my_calloc.c
** File description:
** allocates memory in heap memory zone with null bytes
*/

#include <stddef.h>
#include <stdlib.h>

void *my_calloc(size_t size)
{
    char *obj = malloc(size);

    if (!obj)
        return NULL;
    for (int i = 0; i < size; i++)
        obj[i] = 0;
    return obj;
}
