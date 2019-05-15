/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** and instruction
*/

#include "vm.h"
#include "op.h"

int op_and(environment_t *env)
{
    int index = INSTRUCTION(env);

    if (index != 0x06)
        return (1);
    return (0);
}