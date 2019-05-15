/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** and instruction
*/

#include "vm.h"
#include "op.h"

int op_and(unsigned char *arena, process_t *proc)
{
    int index = INDEX(arena, proc);

    if (index != 0x06)
        return (1);
    return (0);
}