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

/*                  Process structure                       */
typedef struct process_list_s {
    int fd;                                 // binary file fd closed when champion is load in memory
    short pc;                               // program counter (offset from address to current instruction) in 2 bytes
    int cycles_left;                        // cycles left before instruction execution
    int cycles_to_die;                      // cycles left before death if no live instruction is called
    header_t header;                        // header of the binary
    int registers[REG_NUMBER][REG_SIZE];    // registers of the binary
    unsigned int prog_number;               // actual programm number
    unsigned long int address;              // address of the first programm instruction
    struct process_list_s *next;            // pointer to next process
} process_t;

/*                  VM structure                       */
typedef struct environment_s {
    int nbr_cycle;                          // used with --dump to display memory
    int cycle_to_die;                       // global Cycle to die that will be updated
    unsigned int live_instruction_nb;       // global count of live instruction calls
    unsigned char arena[MEM_SIZE];          // equivalent of RAM memory
    process_t *processes_tail;              // end of processes linked list
    process_t *processes_head;              // beginning of proccesses list
} environment_t;

#define PROC_TAIL(env) (env->processes_tail)    // gives the current process focused by scheduler
#define PROC_HEAD(env) (env->processes_head)    // gives the beginning of the process list

static const int ERROR = 84;                // error code


//  Reads all the given program parameters and create a first processes
//  list and fill their beginning address and prog nb if specified
environment_t *read_parameters(int argc, char **argv);

//  Reads binary header and check its validity. It also removes little endian
//  on prog size and set all the memory start address and writes champions
int load_champions(environment_t *env);

// Returns the given list len
int get_list_len(process_t *head);

// Main loop of the VM. It exec for each process currently alive, the current
// instruction and update pc, cycles_left, cycles_to_die if necessary.
int run_vm(environment_t *env);

// gives the NBth bit pairs in a byt
// expl with byte = 10 01 11 01
//  nb = 0 => 0b01
//  nb = 1 => 0b11 ...
#define GET_BITS(byte, nb) ((byte >> (2 * nb)) & 0b11)

// gives the current instruction mnemonique (ex: 0x01 if live is the current instruction)
#define INSTRUCTION(env) (env->arena[(env->processes_tail->address + env->processes_tail->pc) % MEM_SIZE])

/*                  INSTRUCTIONS                    */
// all operations return the offset by which the programm pc is incremented
// in case of error an operations return 1 so that the pc is set to the next
// byte

static const int OP_ERROR = 1; // operation error code

// code: 0x01
// size:
// coding_byte:
// parameters:
// action:
int op_live(environment_t *env);

// code: 0x02
// size:
// coding_byte:
// parameters:
// action:
int op_ls(environment_t *env);

// code: 0x03
// size:
// coding_byte:
// parameters:
// action:
int op_st(environment_t *env);

// code: 0x04
// size: 5
// coding_byte: yes
// parameters: 3 registers
// action: arg3 = arg1 + arg2
int op_add(environment_t *env);

// code: 0x05
// size: 5
// coding_byte: yes
// parameters: 3 registers
// action: arg3 = arg1 - arg2
int op_sub(environment_t *env);

// code: 0x06
// size:
// coding_byte:
// parameters:
// action:
int op_and(environment_t *env);

// code: 0x07
// size:
// coding_byte:
// parameters:
// action:
int op_or(environment_t *env);

// code: 0x08
// size:
// coding_byte:
// parameters:
// action:
int op_xor(environment_t *env);

// code: 0x09
// size:
// coding_byte:
// parameters:
// action:
int op_zjmp(environment_t *env);

// code: 0x0a
// size:
// coding_byte:
// parameters:
// action:
int op_ldi(environment_t *env);

// code: 0x0b
// size:
// coding_byte:
// parameters:
// action:
int op_sti(environment_t *env);

// code: 0x0c
// size:
// coding_byte:
// parameters:
// action:
int op_fork(environment_t *env);

// code: 0x0d
// size:
// coding_byte:
// parameters:
// action:
int op_lld(environment_t *env);

// code: 0x0e
// size:
// coding_byte:
// parameters:
// action:
int op_lldi(environment_t *env);

// code: 0x0f
// size:
// coding_byte:
// parameters:
// action:
int op_lfork(environment_t *env);

// code: 0x10
// size: 3
// coding_byte: yes
// parameters: one register
// action: prints the ascii character stored in the register
int op_aff(environment_t *env);

#endif /* !VM_H_ */
