/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** st instruction
*/

#include "vm.h"
#include "op.h"

int op_st(environment_t *env)
{
    int offset = PROC_TAIL(env)->address + PROC_TAIL(env)->pc;
    char coding_byte = env->arena[(offset + 1) % MEM_SIZE];
    char reg = env->arena[(offset + 2) % MEM_SIZE] % REG_NUMBER;
    int tmp = 0;

    if (INSTRUCTION(env) != 0x03 || GET_BITS(coding_byte, 3) != 0b01 ||
    GET_BITS(coding_byte, 1) != 0b00 || GET_BITS(coding_byte, 0) != 0b00)
        return (OP_ERROR);
    switch (GET_BITS(coding_byte, 2)) {
        case 0b01:
            PROC_TAIL(env)->registers[env->arena[(PROC_TAIL(env)->address
            + PROC_TAIL(env)->pc + 3) % MEM_SIZE] % REG_NUMBER] =
            PROC_TAIL(env)->registers[reg];
            return (4);
        case 0b10:
            tmp = env->arena[(offset + 3) % MEM_SIZE] << 8
            | env->arena[(offset + 4) % MEM_SIZE];
            env->arena[(offset + tmp) % MEM_SIZE] =
            PROC_TAIL(env)->registers[reg];
            return (5);
        case 0b11:
            tmp = env->arena[(offset + 3) % MEM_SIZE] << 24
            | env->arena[(offset + 4) % MEM_SIZE] << 16
            | env->arena[(offset + 5) % MEM_SIZE] << 8
            | env->arena[(offset + 6) % MEM_SIZE];
            env->arena[(offset + tmp % IDX_MOD) % MEM_SIZE] =
            PROC_TAIL(env)->registers[reg];
            return (7);
    }
    return (OP_ERROR);
}