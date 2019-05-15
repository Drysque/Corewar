/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** sub instruction
*/

#include "vm.h"
#include "op.h"

int op_sub(environment_t *env)
{
    int index = INSTRUCTION(env);
    char coding_byte = (env->arena[(PROC_TAIL(env)->address +
    PROC_TAIL(env)->pc + 1) % MEM_SIZE]);

    if (index != 0x05 || coding_byte !=
    (0b01 << 6 | 0b01 << 4 | 0b01 << 2 | 0b00))
        return (OP_ERROR);
    PROC_TAIL(env)->registers[(PROC_TAIL(env)->address +
    PROC_TAIL(env)->pc + 4) % MEM_SIZE][0] =
    (PROC_TAIL(env)->address + PROC_TAIL(env)->pc + 2) -
    (PROC_TAIL(env)->address + PROC_TAIL(env)->pc + 3);
    return (5);
}