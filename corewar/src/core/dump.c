/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** dump
*/

#include "vm.h"
#include "my.h"

void dump_arena(char arena[MEM_SIZE])
{
    for (int i = 0; i < MEM_SIZE; i += 1) {
        my_printf("%x", arena[i]);
        if (i % 32 == 0)
            my_printf("\n%x\t", i * 32);
    }
    my_printf("\n");
}