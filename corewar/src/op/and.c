/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** and instruction
*/

#include "vm.h"
#include "asm.h"
#include "op.h"
#include "my.h"

static const char INDEXES[] = {0x05, 0x09, 0x0a, 0x0b, 0x0c, 0x0f, 0x0};


static int get_case_direct(environment_t *env, int offset, int *shift)
{
    int res = 0;

    if (is_one_of_them(INSTRUCTION(env), INDEXES)) {
        res = env->arena[(offset + 2 + *shift) % MEM_SIZE] << 8
        | env->arena[(offset + 3 + *shift) % MEM_SIZE];
        *shift += 2;
    } else {
        res = env->arena[(offset + *shift + 2) % MEM_SIZE] << 24
        | env->arena[(offset + *shift + 3) % MEM_SIZE] << 16
        | env->arena[(offset + *shift + 4) % MEM_SIZE] << 8
        | env->arena[(offset + *shift + 5) % MEM_SIZE];
        *shift += 4;
    }
    return (res);
}

static int get_case_indirect(environment_t *env, int offset, int *shift)
{
    int res = 0;

    res = env->arena[(offset + 2 + *shift) % MEM_SIZE] << 8
    | env->arena[(offset + 3 + *shift) % MEM_SIZE];
    *shift += 2;
    return (res);
}

int get_arg(environment_t *env, int arg_nb)
{
    int offset = PROC_TAIL(env)->address + PROC_TAIL(env)->pc;
    int res = 0;
    int shift = 0;
    int tmp = 0;

    for (int i = 1; i <= arg_nb; i += 1) {
        tmp = 4 - i;
        switch (GET_BITS(env->arena[(offset + 1) % MEM_SIZE], tmp)) {
            case 0b01:
                res = (int)env->arena[(offset + shift++ + 2) %
                MEM_SIZE] % REG_NUMBER;
                shift += 1;
                break;
            case 0b11:
                res = get_case_indirect(env, offset, &shift);
                break;
            case 0b10:
                res = get_case_direct(env, offset, &shift);
        }
    }
    return (res);
}

int get_instruction_size(environment_t *env)
{
    int len = 2;

    for (int i = 0; i < 4; i += 1) {
        switch (GET_BITS(env->arena[(PROC_TAIL(env)->address +
        PROC_TAIL(env)->pc + 1) % MEM_SIZE], i)) {
            case 0b01:
                len += 1;
                break;
            case 0b10:
                len += (is_one_of_them(INSTRUCTION(env), INDEXES) ? 2 : 4);
                break;
            case 0b11:
                len += 2;
                break;
        }
    }
    return (len);
}

int op_and(environment_t *env)
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
    PROC_TAIL(env)->registers[arg3] = arg1 & arg2;
    PROC_TAIL(env)->carry = 1;
    return (get_instruction_size(env));
}