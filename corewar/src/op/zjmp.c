/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** zjmp instruction
*/

#include "vm.h"
#include "op.h"

int op_zjmp(environment_t *env)
{
    int offset = PROC_TAIL(env)->address + PROC_TAIL(env)->pc;

    if (INSTRUCTION(env) != 0x09 || PROC_TAIL(env)->carry != 1)
        return (OP_ERROR);
    PROC_TAIL(env)->pc +=
    (env->arena[offset + 1] << 8 | env->arena[offset + 2]) % IDX_MOD;
    return (3);
}