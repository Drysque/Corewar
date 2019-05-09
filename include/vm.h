/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** vm header
*/

#ifndef VM_H_
    #define VM_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct processes_s {
    char *name;
    unsigned int prog_number;
    unsigned long int address;
    struct processes_s *next;
} processes_t;

typedef struct environment_s {
    unsigned int nbr_cycle;
    processes_t *processes_tail;
    processes_t *processes_head;
} environment_t;

#define PROC_TAIL(env) (env->processes_tail)
#define PROC_HEAD(env) (env->processes_head)

static const int ERROR = 84;

environment_t *read_parameters(int argc, char **argv);

#endif /* !VM_H_ */
