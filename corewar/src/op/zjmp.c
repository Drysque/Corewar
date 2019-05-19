/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** zjmp instruction
*/

#include "vm.h"
#include "op.h"
#include "asm.h"

int op_zjmp(environment_t *env)
{
    int offset = PROC_TAIL(env)->address + PROC_TAIL(env)->pc;
    short nb = (env->arena[(offset + 1) % MEM_SIZE] << 8 |
    env->arena[(offset + 2) % MEM_SIZE]);

    if (INSTRUCTION(env) != 0x09 || PROC_TAIL(env)->carry != 1)
        return (OP_ERROR);
    PROC_TAIL(env)->pc += (nb % IDX_MOD);
    return (0);
}