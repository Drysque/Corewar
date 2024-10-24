/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** run vm
*/

#include "vm.h"
#include "op.h"
#include "my.h"

void init_processes(environment_t *env)
{
    for (process_t *tail = PROC_HEAD(env); tail; tail = tail->next) {
        tail->cycles_left = op_tab[INSTRUCTION(env) % 16].nbr_cycles;
        tail->cycles_to_die = env->cycle_to_die;
        tail->registers[1] = tail->prog_number;
        tail->pc = 0;
        tail->carry = 0;
    }
}

int run_instruction(environment_t *env)
{
    static int (*inst_tab[])(environment_t *env) =
    {&op_live, &op_ld, &op_st, &op_add, &op_sub,
    &op_and, &op_or, &op_xor, &op_zjmp, &op_ldi,
    &op_sti, &op_fork, &op_lld, &op_lldi, &op_lfork,
    &op_aff};
    int index = (INSTRUCTION(env) - 1) % 16;

    if (index < 0)
        return (OP_ERROR);
    return (inst_tab[index](env));
}

void check_cycles(environment_t *env)
{
    if (PROC_TAIL(env)->cycles_to_die <= 0)
        return;
    PROC_TAIL(env)->cycles_to_die -= 1;
    if (PROC_TAIL(env)->cycles_to_die <= 0)
        return;
    if (PROC_TAIL(env)->cycles_left == 0) {
        PROC_TAIL(env)->pc += run_instruction(env);
        if (PROC_TAIL(env)->pc < 0)
            PROC_TAIL(env)->pc = 0;
        PROC_TAIL(env)->cycles_left =
        op_tab[INSTRUCTION(env) % 16].nbr_cycles;
    } else
        PROC_TAIL(env)->cycles_left -= 1;
}

static bool check_end(environment_t *env)
{
    int alive = 0;

    for (process_t *ptr = PROC_HEAD(env); ptr; ptr = ptr->next)
        if (ptr->cycles_to_die > 0)
            alive++;
    return (alive > 1);
}

int run_vm(environment_t *env)
{
    int cycles = env->nbr_cycle;

    PROC_TAIL(env) = PROC_HEAD(env);
    env->cycle_to_die = CYCLE_TO_DIE;
    init_processes(env);
    while (check_end(env) && env->cycle_to_die > 0) {
        while (PROC_TAIL(env) && env->cycle_to_die > 0) {
            check_cycles(env);
            PROC_TAIL(env) = PROC_TAIL(env)->next;
        }
        PROC_TAIL(env) = PROC_HEAD(env);
        if (cycles-- < 0 && env->nbr_cycle != 0) {
            dump_arena(env->arena);
            cycles = env->nbr_cycle;
        }
    }
    my_printf("The player %d(%s) has won.\n", env->last_player_alive,
    get_list_index(PROC_HEAD(env), env->last_player_alive)->header
    .prog_name);
    return (0);
}
