/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** fork instruction
*/

#include "vm.h"
#include "op.h"
#include "my.h"
#include "asm.h"

void my_memcpy(void *dest, void *src, size_t size)
{
    for (size_t i = 0; i < size; i += 1)
        ((char *)dest)[i] = ((char *)src)[i];
}

int op_fork(environment_t *env)
{
    int offset = (PROC_TAIL(env)->address + PROC_TAIL(env)->pc) % MEM_SIZE;
    short new_offset = (((env->arena[(offset + 1) % MEM_SIZE] << 8) |
    (env->arena[(offset + 2) % MEM_SIZE])) % IDX_MOD) % MEM_SIZE;
    process_t *tmp = NULL;

    if (INSTRUCTION(env) != 0x0c)
        return (OP_ERROR);
    tmp = PROC_TAIL(env)->next;
    PROC_TAIL(env)->next = my_calloc(sizeof(process_t));
    if (!PROC_TAIL(env)->next)
        my_error("FATAL ERROR: Malloc failed\n");
    my_memcpy(PROC_TAIL(env)->next, PROC_TAIL(env), sizeof(process_t));
    PROC_TAIL(env)->next->pc = PROC_TAIL(env)->pc + new_offset;
    if (PROC_TAIL(env)->next->pc < 0)
        PROC_TAIL(env)->next->pc = 0;
    PROC_TAIL(env)->next->next = tmp;
    return (3);
}