/*
** EPITECH PROJECT, 2019
** offset_manage.c
** File description:
** registers written bytes
*/

#include "asm.h"
#include "my.h"

off_t offset_pos(ssize_t written, int status)
{
    static off_t offset = 0;

    if (status == ADD)
        offset += written;
    if (status == SUB)
        offset -= written;
    return offset;
}
