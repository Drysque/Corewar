/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** run vm
*/

#include "vm.h"
#include "op.h"
#include "my.h"

// init for each process the cycles_left, the cycles_to_die, pc and the r1 register

static void init_processes(environment_t *env)
{
    for (process_t *tail = PROC_HEAD(env); tail; tail = tail->next) {
        tail->cycles_left = op_tab[INSTRUCTION(env) % 16].nbr_cycles;
        tail->cycles_to_die = env->cycle_to_die;
        tail->registers[0] = tail->prog_number;
        tail->pc = 0;
        tail->carry = 0;
    }
}

//  deletes current process from proccess list

static void delete_current_process(environment_t *env)
{
    return;
}

//  call the current instruction execution

static int run_instruction(environment_t *env)
{
    static int (*inst_tab[])(environment_t *env) =
    {&op_live, &op_ld, &op_st, &op_add, &op_sub,
    &op_and, &op_or, &op_xor, &op_zjmp, &op_ldi,
    &op_sti, &op_fork, &op_lld, &op_lldi, &op_lfork,
    &op_aff};
    int index = (INSTRUCTION(env) - 1) % 16;

    if (index < 0)                              // index < 0 si on arrive en dehors du programme (case mémoire de valeur 0 par expl)
        return (OP_ERROR);
    return (inst_tab[index](env));
}

//  checks and updates global cycle_to_die and cycle_to_die and cycle_left

static void check_cycles(environment_t *env)
{
    if (PROC_TAIL(env)->cycles_to_die <= 0)
        return;
    // printf("%d\n", PROC_TAIL(env)->cycles_to_die);
    PROC_TAIL(env)->cycles_to_die -= 1;
    if (PROC_TAIL(env)->cycles_to_die <= 0) {
        printf("PROGRAMM %d DIED\n", PROC_TAIL(env)->prog_number);
        // PROC_TAIL(env)->cycles_to_die = env->cycle_to_die;         // il faut reset au nouveau cycle to die ?
        delete_current_process(env);
        return;
    }
    if (PROC_TAIL(env)->cycles_left == 0) {
        printf("INSTRUCTION EXECUTED %x PC: %d\n", INSTRUCTION(env), PROC_TAIL(env)->pc);
        PROC_TAIL(env)->pc += run_instruction(env);
        PROC_TAIL(env)->cycles_left = op_tab[INSTRUCTION(env) % 16].nbr_cycles;
    } else
        PROC_TAIL(env)->cycles_left -= 1;
    // printf("CYCLE NB: %d\n", PROC_TAIL(env)->cycles_left);
}

//  main function of vm run: calls init of cycles and go through all processes
//  while the are at least two processes alive
int run_vm(environment_t *env)
{
    PROC_TAIL(env) = PROC_HEAD(env);
    env->cycle_to_die = CYCLE_TO_DIE;
    init_processes(env);
    while (env->cycle_to_die > 0) {                             // global cycle_to_die is changed in live instruction
        while (PROC_TAIL(env) && env->cycle_to_die > 0) {
            check_cycles(env);
            PROC_TAIL(env) = PROC_TAIL(env)->next;
        }
        PROC_TAIL(env) = PROC_HEAD(env);
    }
    return (0);
}