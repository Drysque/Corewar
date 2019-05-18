/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** sti instruction
*/

#include "vm.h"
#include "op.h"

int op_sti(environment_t *env)
{
    int offset = PROC_TAIL(env)->address + PROC_TAIL(env)->pc;
    char coding_byte = env->arena[(offset + 1) % MEM_SIZE];
    int index = 0;
    int new_offset = 0;

    if (INSTRUCTION(env) != 0x0b || GET_BITS(coding_byte, 3) != 0b01
    || GET_BITS(coding_byte, 0) != 0b00 || GET_BITS(coding_byte, 1) == 0b00 ||
    GET_BITS(coding_byte, 2) == 0b00)
        return (OP_ERROR);
    index = get_arg(env, 1);
    new_offset = (get_arg(env, 2) + get_arg(env, 3)) % IDX_MOD;
    env->arena[(offset + new_offset) % MEM_SIZE] = GET_BITS(PROC_TAIL(env)->registers[index], 3);
    env->arena[(offset + new_offset + 1) % MEM_SIZE] =
    GET_BITS(PROC_TAIL(env)->registers[index], 2);
    env->arena[(offset + new_offset + 2) % MEM_SIZE] =
    GET_BITS(PROC_TAIL(env)->registers[index], 1);
    env->arena[(offset + new_offset + 3) % MEM_SIZE] =
    GET_BITS(PROC_TAIL(env)->registers[index], 0);
    return (get_instruction_size(env));
}
