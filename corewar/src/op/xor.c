/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** xor instruction
*/

#include "vm.h"
#include "op.h"

int op_xor(environment_t *env)
{
    char coding_byte = env->arena[(PROC_TAIL(env)->address +
    PROC_TAIL(env)->pc + 1) % MEM_SIZE];
    int arg1 = 0;
    int arg2 = 0;
    int arg3 = 0;

    PROC_TAIL(env)->carry = 0;
    if (INSTRUCTION(env) != 0x06 || GET_BITS(coding_byte, 0) != 0b00 ||
    GET_BITS(coding_byte, 1) != 0b01)
        return (OP_ERROR);
    arg1 = get_arg(env, 1);
    arg2 = get_arg(env, 2);
    arg3 = get_arg(env, 3);
    PROC_TAIL(env)->registers[arg3] = (arg1 ^ arg2);
    PROC_TAIL(env)->carry = 1;
    return (get_instruction_size(env));
}