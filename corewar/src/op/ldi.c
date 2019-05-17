/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** ldi instruction
*/

#include "vm.h"
#include "op.h"

int op_ldi(environment_t *env)
{
    PROC_TAIL(env)->carry = 0;
    PROC_TAIL(env)->carry = 1;
    return 0;
}