/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** live instruction
*/

#include "vm.h"
#include "op.h"
#include "my.h"

process_t *get_list_index(process_t *head, int nb)
{
    while (head) {
        if (head->prog_number == nb)
            return (head);
        head = head->next;
    }
    return (NULL);
}

int op_live(environment_t *env)
{
    int offset = PROC_TAIL(env)->address + PROC_TAIL(env)->pc;
    int value = 0;
    process_t *ptr = NULL;

    if (GET_BITS(env->arena[offset + 1], 0) ||
        GET_BITS(env->arena[offset + 1], 1) ||
        GET_BITS(env->arena[offset + 1], 2))
        return OP_ERROR;
    value = env->arena[offset + 1] << 24 | env->arena[offset + 2] << 16
        | env->arena[offset + 3] << 8 | env->arena[offset + 4];
    ptr = get_list_index(PROC_HEAD(env), value);
    if (!ptr)
        return (OP_ERROR);
    my_printf("The player %d (%s)is alive\n", value, ptr->header.prog_name);
    PROC_TAIL(env)->cycles_to_die = env->cycle_to_die;
    env->live_instruction_nb += 1;
    env->last_player_alive = ptr->prog_number;
    if (env->live_instruction_nb >= NBR_LIVE)
        env->cycle_to_die -= CYCLE_DELTA;
    return (1 + DIR_SIZE);
}