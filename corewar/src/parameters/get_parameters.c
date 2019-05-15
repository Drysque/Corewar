/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** get all arguments given to the virtual machine
*/

#include <stdio.h>
#include "vm.h"
#include "my.h"

static int add_to_current_process(environment_t *env, char **argv,
bool in_process)
{
    bool created = false;
    (void)argv;

    if (PROC_HEAD(env) == NULL) {
        PROC_HEAD(env) = malloc(sizeof(processes_t));
        if (PROC_HEAD(env) == NULL)
            return (ERROR);
        PROC_TAIL(env) = PROC_HEAD(env);
        created = true;
    } else if (!in_process) {
        PROC_TAIL(env)->next = malloc(sizeof(processes_t));
        if (PROC_TAIL(env)->next == NULL)
            return (ERROR);
        PROC_TAIL(env) = PROC_TAIL(env)->next;
        created = true;
    }
    if (created) {
        PROC_TAIL(env)->next = NULL;
        PROC_TAIL(env)->address = 0;
        PROC_TAIL(env)->prog_number = 0;
        PROC_TAIL(env)->name = NULL;
    }
    return (0);
}

static int get_flag(char **argv, environment_t *env,
int *index, bool *in_process)
{
    printf("[%s:%d] => %s\n", __FILE__, __LINE__, argv[*index]);
    if (argv[*index] == NULL)
        return (ERROR);
    if (my_strcmp(argv[*index], "-a")) {
        if (argv[*index + 1] == NULL || my_getnbr(argv[*index + 1]) <= 0)
            return (ERROR);
        PROC_TAIL(env)->address = my_getnbr(argv[*index + 1]);
        *index += 1;
        *in_process = true;
        return (PROC_TAIL(env)->address <= 0 ? ERROR : 0);
    }
    if (my_strcmp(argv[*index], "-n")) {
        if (argv[*index + 1] == NULL || my_getnbr(argv[*index + 1]) <= 0)
            return (ERROR);
        PROC_TAIL(env)->prog_number = my_getnbr(argv[*index + 1]);
        *index += 1;
        *in_process = true;
        return (PROC_TAIL(env)->prog_number <= 0 ? ERROR : 0);
    }
    if (my_strcmp(argv[*index - 1], "-dump"))
        return (ERROR);
    PROC_TAIL(env)->name = my_strdup(argv[*index]);
    printf("END OF PROCESS\n");
    *in_process = false;
    return (0);
}

int check_parameters_validity(int argc, char **argv)
{
    int params_only = 1;

    for (int i = 0; argv[i]; i++) {
        if ((argv[i][0] == '-') && (!my_strcmp(argv[i], "-n") && !my_strcmp(argv[i], "-a") && !my_strcmp(argv[i], "-dump")))
            return (1);
        if (argv[i][0] != '-')
            params_only = 0;
    }
    if (params_only)
        return (1);
    return (0);
}

environment_t *read_parameters(int argc, char **argv)
{
    environment_t *new = NULL;
    bool in_process = true;
    int index = 1;

    new = malloc(sizeof(environment_t));
    new->processes_tail = NULL;
    new->processes_head = NULL;
    if ((index <= argc && new == NULL) || check_parameters_validity(argc, argv))
        return (NULL);
    printf("lol");
    if (my_strcmp(argv[index], "-dump") && index + 2 <= argc) {
        if (my_getnbr(argv[index + 1]) <= 0)
            return (NULL);
        new->nbr_cycle = my_getnbr(argv[index + 1]);
        index += 2;
    }
    while (index < argc) {
        if (add_to_current_process(new, argv, in_process) == ERROR)
            return (NULL);
        if (get_flag(argv, new, &index, &in_process) == ERROR)
            return (NULL);
        index += 1;
    }
    // printf("\n-dump NBR_CYCLE: %d\n", new->nbr_cycle);
    // if (new->processes_tail != NULL) {
    //     for (processes_t *tail = PROC_HEAD(new); tail != NULL; tail = tail->next) {
    //         printf("========================================================\n");
    //         printf("-n PROG_NBR: %d\n", tail->prog_number);
    //         printf("-a PROG_ADDR: %ld\n", tail->address);
    //         printf("PROG NAME: %s\n", tail->name);
    //     }
    // }
    return (new);
}