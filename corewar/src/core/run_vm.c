/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** run vm
*/

#include "vm.h"
#include "op.h"
#include "my.h"

static void init_processes(environment_t *env)
{
    for (process_t *tail = PROC_HEAD(env); tail; tail = tail->next) {
        if (env->arena[(tail->address + tail->pc) % MEM_SIZE] - 1 < 16)
            tail->cycles_left = op_tab[(int)env->arena[(tail->address + tail->pc)
            % MEM_SIZE] - 1].nbr_cycles;
        tail->cycles_to_die = env->cycle_to_die;
    }
}

static void delete_node(process_t *tail)
{
    return;
}

static int run_instruction(unsigned char *arena, process_t *tail)
{
    int index = arena[(tail->address + tail->pc) % MEM_SIZE] - 1;
    static int (*inst_tab[])(unsigned char *arena, process_t *tail) =
    {&op_live, &op_lld, &op_st, &op_add, &op_sub, &op_and, &op_or, &op_xor, &op_zjmp,
    &op_ldi, &op_sti, &op_fork, &op_lld, &op_lldi, &op_lfork, &op_aff};

    return (inst_tab[index](arena, tail));
}

static void check_cycle(unsigned char *arena, process_t *tail, int *alive)
{
    tail->cycles_to_die -= 1;
    if (tail->cycles_to_die <= 0) {
        *alive -= 1;
        delete_node(tail);
    }
    if (arena[(tail->address + tail->pc) % MEM_SIZE] - 1 >= 16)
        my_error("Instruction out of range\n");
    if (tail->cycles_left == 0) {
        tail->pc += run_instruction(arena, tail);
        tail->cycles_left = op_tab[(int)arena[(tail->address + tail->pc)
        % MEM_SIZE] - 1].nbr_cycles;
    } else
        tail->cycles_left -= 1;
}

int run_vm(environment_t *env)
{
    int alive = get_list_len(PROC_HEAD(env));
    process_t *tail = PROC_HEAD(env);

    env->cycle_to_die = CYCLE_TO_DIE;
    init_processes(env);
    while (alive) {
        while (tail) {
            check_cycle(env->arena, tail, &alive);
            tail = tail->next;
        }
        tail = PROC_HEAD(env);
    }
    return (0);
}