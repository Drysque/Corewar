/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** get all arguments given to the virtual machine
*/

#include <stdio.h>
#include "vm.h"
#include "my.h"

static int add_to_current_process(environment_t *env,
bool in_process)
{
    bool created = false;

    if (PROC_HEAD(env) == NULL) {
        PROC_HEAD(env) = my_calloc(sizeof(process_t));
        if (PROC_HEAD(env) == NULL)
            return (ERROR);
        PROC_TAIL(env) = PROC_HEAD(env);
        created = true;
    } else if (!in_process) {
        PROC_TAIL(env)->next = my_calloc(sizeof(process_t));
        if (PROC_TAIL(env)->next == NULL)
            return (ERROR);
        PROC_TAIL(env) = PROC_TAIL(env)->next;
        created = true;
    }
    if (created) {
        PROC_TAIL(env)->next = NULL;
        PROC_TAIL(env)->address = 0;
        PROC_TAIL(env)->prog_number = 0;
    }
    return (0);
}

static int load_file(char **argv, environment_t *env,
int *index, bool *in_process)
{
    if (my_strcmp(argv[*index - 1], "-dump"))
        return (ERROR);
    PROC_TAIL(env)->fd = open(argv[*index], O_RDONLY);
    if (PROC_TAIL(env)->fd == -1) {
        free(PROC_TAIL(env));
        PROC_TAIL(env) = NULL;
        for (process_t *tail = PROC_HEAD(env); tail != NULL;
        tail = tail->next)
            PROC_TAIL(env) = tail;
    }
    *in_process = false;
    return (0);
}

static int get_flag(char **argv, environment_t *env,
int *index, bool *in_process)
{
    if (argv[*index] == NULL)
        return (ERROR);
    if (my_strcmp(argv[*index], "-a")) {
        if (argv[*index + 1] == NULL || my_getnbr(argv[*index + 1]) < 0)
            return (ERROR);
        PROC_TAIL(env)->address = my_getnbr(argv[*index + 1]) % MEM_SIZE;
        *index += 1;
        *in_process = true;
        return (0);
    }
    if (my_strcmp(argv[*index], "-n")) {
        if (argv[*index + 1] == NULL || my_getnbr(argv[*index + 1]) <= 0)
            return (ERROR);
        PROC_TAIL(env)->prog_number = my_getnbr(argv[*index + 1]);
        *index += 1;
        *in_process = true;
        return (PROC_TAIL(env)->prog_number <= 0 ? ERROR : 0);
    }
    return (load_file(argv, env, index, in_process));
}

int check_parameters_validity(char **argv)
{
    int params_only = 1;

    for (int i = 0; argv[i]; i++) {
        if ((argv[i][0] == '-') && (!my_strcmp(argv[i], "-n") &&
        !my_strcmp(argv[i], "-a") && !my_strcmp(argv[i], "-dump")))
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
    environment_t *new = my_calloc(sizeof(environment_t));
    bool in_process = true;
    int index = 1;

    if ((index <= argc && new == NULL) ||
    check_parameters_validity(argv))
        return (NULL);
    if (my_strcmp(argv[index], "-dump") && index + 2 <= argc) {
        if (my_getnbr(argv[index + 1]) <= 0)
            return (NULL);
        new->nbr_cycle = my_getnbr(argv[index + 1]);
        index += 2;
    }
    while (index < argc) {
        if (add_to_current_process(new, in_process) == ERROR)
            return (NULL);
        if (get_flag(argv, new, &index, &in_process) == ERROR)
            return (NULL);
        index += 1;
    }
    return (new);
}