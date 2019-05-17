/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** ldi instruction
*/

#include "vm.h"
#include "op.h"

#warning "doesn't really work..."
int op_ldi(environment_t *env)
{
    int offset = PROC_TAIL(env)->address + PROC_TAIL(env)->pc;
    char coding_byte = env->arena[(offset + 1) % MEM_SIZE];
    int op = 0;
    int res = 0;

    printf("\nWELCOME TO LDI\n");
    PROC_TAIL(env)->carry = 0;
    if (INSTRUCTION(env) != 0x0a || GET_BITS(coding_byte, 3) == 0b01 ||
    GET_BITS(coding_byte, 2) == 0b01 || GET_BITS(coding_byte, 1) != 0b01
    || GET_BITS(coding_byte, 0) != 0b00)
        return (OP_ERROR);
    for (int i = 0; i < IND_SIZE; i += 1)
        op |= (env->arena[(offset + get_arg(env, 1) % IDX_MOD + i) % MEM_SIZE] <<
        ((IND_SIZE - i) * 4));
    printf("op= %d\n", op);
    op += get_arg(env, 2);
    printf("op= %d\n", op);
    for (int i = 0; i < IND_SIZE; i += 1)
        res |= (env->arena[(offset + op % IDX_MOD + i) % MEM_SIZE] <<
        ((IND_SIZE - i) * 4));
    PROC_TAIL(env)->carry = 1;
    printf("r%d = %d\n", get_arg(env, 3) % REG_NUMBER, res);
    PROC_TAIL(env)->registers[get_arg(env, 3) % REG_NUMBER] = res;
    return (get_instruction_size(env));
}