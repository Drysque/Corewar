/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** aff instruction
*/

#include "vm.h"
#include "op.h"
#include "my.h"

int op_aff(environment_t *env)
{
    int index = INSTRUCTION(env) % 16;
    char coding_byte = (env->arena[(PROC_TAIL(env)->address
    + PROC_TAIL(env)->pc + 1) % MEM_SIZE]);

    if (index != 0x10 || coding_byte !=
    (0b01 << 6 | 0b00 << 4 | 0b00 << 2 | 0b00))
        return (1);
    my_printf("%d\n",
    (PROC_TAIL(env)->registers[(PROC_TAIL(env)->address
    + PROC_TAIL(env)->pc + 2) % MEM_SIZE][0]) % 256);
    return (3);
}