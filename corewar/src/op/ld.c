/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** ld instruction
*/

#include "vm.h"
#include "op.h"

int op_ld(environment_t *env)
{
    int offset = PROC_TAIL(env)->address + PROC_TAIL(env)->pc;
    int arg = 0;
    int r = 0;

    PROC_TAIL(env)->carry = 0;
    if (INSTRUCTION(env) != 0x02)
        return OP_ERROR;
    if (GET_BITS(env->arena[offset + 1], 0) ||
        GET_BITS(env->arena[offset + 1], 0) ||
        GET_BITS(env->arena[offset + 1], 2) != 0b01)
        return OP_ERROR;
    r = get_arg(env, 2) % REG_NUMBER;
        arg = get_arg(env, 1) % IDX_MOD;
    if (GET_BITS(env->arena[offset + 1], 3) == 0b11)
        PROC_TAIL(env)->registers[r] = env->arena[(offset + arg) % MEM_SIZE];
    else if (GET_BITS(env->arena[offset + 1], 3) == 0b10)
        PROC_TAIL(env)->registers[r] = arg;
    else
        return OP_ERROR;
    PROC_TAIL(env)->carry = 1;
    return get_instruction_size(env);
}