/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** lld instruction
*/

#include "vm.h"
#include "op.h"

int op_lld(environment_t *env)
{
    int offset = PROC_TAIL(env)->address + PROC_TAIL(env)->pc;
    int arg = 0;
    int reg = 0;

    PROC_TAIL(env)->carry = 0;
    printf("=> entering LLD\n");
    PROC_TAIL(env)->carry = 0;
    if (INSTRUCTION(env) != 0x02)
        return OP_ERROR;
    if (GET_BITS(env->arena[offset + 1], 0) ||
        GET_BITS(env->arena[offset + 1], 0) ||
        GET_BITS(env->arena[offset + 1], 2) != 0b01)
        return OP_ERROR;
    reg = get_arg(env, 2);
    printf("LLD asked second arg (register) r%d\n", reg);
    if (GET_BITS(env->arena[offset + 1], 3) == 0b11) {
        arg = get_arg(env, 1);
        printf("LLD asked first arg (indirect): loading arena[%d] (%d) into register %d\n", (offset + arg) % MEM_SIZE, env->arena[(offset + arg) % MEM_SIZE], reg);
        PROC_TAIL(env)->registers[reg] = env->arena[(offset + arg) % MEM_SIZE];
    }
    else if (GET_BITS(env->arena[offset + 1], 3) == 0b10) {
        arg = get_arg(env, 1);
        printf("LLD asked first arg (direct): loading %d into register %d\n", arg, reg);
        PROC_TAIL(env)->registers[reg] = arg;
    }
    else
        return OP_ERROR;
    PROC_TAIL(env)->carry = 1;
    return get_instruction_size(env);
    PROC_TAIL(env)->carry = 1;
    return 0;
}