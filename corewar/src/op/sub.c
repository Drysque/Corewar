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

    PROC_TAIL(env)->carry = 0;
    if (index != 0x04 || coding_byte !=
    (0b01 << 6 | 0b01 << 4 | 0b01 << 2 | 0b00))
        return (OP_ERROR);
    PROC_TAIL(env)->registers[env->arena[(PROC_TAIL(env)->address +
    PROC_TAIL(env)->pc + 4) % MEM_SIZE] % REG_NUMBER] =
    PROC_TAIL(env)->registers[env->arena[(PROC_TAIL(env)->address
    + PROC_TAIL(env)->pc + 2) % MEM_SIZE] % REG_NUMBER] -
    PROC_TAIL(env)->registers[env->arena[(PROC_TAIL(env)->address
    + PROC_TAIL(env)->pc + 3) % MEM_SIZE] % REG_NUMBER];
    PROC_TAIL(env)->carry = 1;
    return (5);
}