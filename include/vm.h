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
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "op.h"

typedef struct process_list_s {
    int fd;
    short pc;
    int cycles_left;
    int cycles_to_die;
    header_t header;
    int registers[REG_NUMBER][REG_SIZE];
    unsigned int prog_number;
    unsigned long int address;
    struct process_list_s *next;
} process_t;

typedef struct environment_s {
    int cycle_to_die;
    unsigned int live_instruction_nb;
    unsigned char arena[MEM_SIZE];
    int nbr_cycle;
    process_t *processes_tail;
    process_t *processes_head;
} environment_t;

#define PROC_TAIL(env) (env->processes_tail)
#define PROC_HEAD(env) (env->processes_head)

static const int ERROR = 84;

environment_t *read_parameters(int argc, char **argv);
int load_champions(environment_t *env);
int get_list_len(process_t *head);
int run_vm(environment_t *env);

#define GET_BITS(byte, nb) ((byte >> (2 * nb)) & 0b11)
#define INDEX(arena, tail) (arena[(tail->address + tail->pc) % MEM_SIZE] - 1)

/*                  INSTRUCTIONS                    */

int op_live(unsigned char *arena, process_t *tail);
int op_ls(unsigned char *arena, process_t *tail);
int op_st(unsigned char *arena, process_t *tail);
int op_add(unsigned char *arena, process_t *tail);
int op_sub(unsigned char *arena, process_t *tail);
int op_and(unsigned char *arena, process_t *tail);
int op_or(unsigned char *arena, process_t *tail);
int op_xor(unsigned char *arena, process_t *tail);
int op_zjmp(unsigned char *arena, process_t *tail);
int op_ldi(unsigned char *arena, process_t *tail);
int op_sti(unsigned char *arena, process_t *tail);
int op_fork(unsigned char *arena, process_t *tail);
int op_lld(unsigned char *arena, process_t *tail);
int op_lldi(unsigned char *arena, process_t *tail);
int op_lfork(unsigned char *arena, process_t *tail);
int op_aff(unsigned char *arena, process_t *tail);

#endif /* !VM_H_ */
