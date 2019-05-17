/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** fork instruction
*/

#include "vm.h"
#include "op.h"
#include "my.h"

static void my_memcpy(void *dest, void *src)
{
    for (int i = 0; i < sizeof(src); i += 1)
        ((char *)dest)[i] = ((char *)src)[i];
}

int op_fork(environment_t *env)
{
    int offset = (PROC_TAIL(env)->address + PROC_TAIL(env)->pc) % MEM_SIZE;
    int new_offset = (offset + (env->arena[offset + 1] << 8 | env->arena[offset + 2]) % IDX_MOD ) % MEM_SIZE;
    void *tmp = NULL;

    for (int i = 0; i < PROC_TAIL(env)->header.prog_size; i += 1)
        env->arena[i + new_offset] = env->arena[i + PROC_TAIL(env)->address];
    tmp = PROC_TAIL(env)->next;
    PROC_TAIL(env)->next = my_calloc(sizeof(process_t));
    if (!PROC_TAIL(env)->next)
        my_error("FATAL ERROR: Malloc failed\n");
    PROC_TAIL(env)->next->address = new_offset;
    PROC_TAIL(env)->cycles_to_die = env->cycle_to_die;
    my_memcpy(&PROC_TAIL(env)->header, &PROC_TAIL(env)->next->header);
    PROC_TAIL(env)->next->prog_number = rand() % 1024;
    #warning "PROG NB"
    PROC_TAIL(env)->next->next = tmp;
    return 0;
}