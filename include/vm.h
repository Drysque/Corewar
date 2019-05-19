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
    // carry is set to 1 if the last instruction worked
    int carry;
    // binary file fd closed when champion is load in memory
    int fd;
    // program counter (offset from address to current instruction) in 2 bytes
    short pc;
    // cycles left before instruction execution
    int cycles_left;
    // cycles left before death if no live instruction is called
    int cycles_to_die;
    // header of the binary
    header_t header;
    // registers of the binary
    int registers[REG_NUMBER];
    // actual programm number
    int prog_number;
    // address of the first programm instruction
    unsigned long int address;
    // pointer to next process
    struct process_list_s *next;
} process_t;

/*                  VM structure                       */
typedef struct environment_s {
    // used with --dump to display memory
    int nbr_cycle;
    // last player to say live is wins
    int last_player_alive;
    // global Cycle to die that will be updated
    int cycle_to_die;
    // global count of live instruction calls
    unsigned int live_instruction_nb;
    // equivalent of RAM memory
    unsigned char arena[MEM_SIZE];
    // end of processes linked list
    process_t *processes_tail;
    // beginning of proccesses list
    process_t *processes_head;
} environment_t;

// gives the current process focused by scheduler
#define PROC_TAIL(env) (env->processes_tail)
// gives the beginning of the process list
#define PROC_HEAD(env) (env->processes_head)

static const int ERROR = 84;                // error code

///  Reads all the given program parameters and create a first processes
///  list and fill their beginning address and prog nb if specified
environment_t *read_parameters(int argc, char **argv);

///  Reads binary header and check its validity. It also removes little endian
///  on prog size and set all the memory start address and writes champions
int load_champions(environment_t *env);

/// Returns the given list len
int get_list_len(process_t *head);

/// gives the content of the arg_nbth parameter of an instruction
/// wheter it is a register, direct or indirect
/// /!\ given instruction must have a coding byte
int get_arg(environment_t *env, int arg_nb);

/// returns len of the current instruction
/// /!\ instruction must have a coding byte
int get_instruction_size(environment_t *env);

/// Main loop of the VM. It exec for each process currently alive, the current
/// instruction and update pc, cycles_left, cycles_to_die if necessary.
int run_vm(environment_t *env);

process_t *get_list_index(process_t *head, int nb);
void my_memcpy(void *dest, void *src, size_t size);
void dump_arena(unsigned char arena[MEM_SIZE]);

/// gives the NBth bit pairs in a byte
/// expl with byte = 10 10 11 01
///  nb = 0 => 0b01
///  nb = 1 => 0b11 ...
#define GET_BITS(byte, nb) ((byte >> (2 * nb)) & 0b11)

/// gives the current instruction mnemonique (ex: 0x01 if live is
/// the current instruction)
#define OFFSET(env) (env->processes_tail->address + env->processes_tail->pc)
#define INSTRUCTION(env) (env->arena[OFFSET(env) % MEM_SIZE])

/*                  INSTRUCTIONS                    */
// all operations return the offset by which the programm pc is incremented
// in case of error an operations return 1 so that the pc is set to the next
// byte

static const int OP_ERROR = 1; // operation error code

/// code: 0x01
/// coding_byte: no
/// parameters: direct
/// action: says live and increment the global nb_live
int op_live(environment_t *env);

/// code: 0x02
/// coding_byte: yes
/// parameters: /
/// action: load a value in memory or in a register
int op_ld(environment_t *env);

/// code: 0x03
/// coding_byte: yes
/// parameters: takes a register and a direct or indirect
/// action: stores the content of the 1st parameter (register) into the 2nd
int op_st(environment_t *env);

/// code: 0x04
/// coding_byte: yes
/// parameters: 3 registers
/// action: arg3 = arg1 + arg2
int op_add(environment_t *env);

/// code: 0x05
/// coding_byte: yes
/// parameters: 3 registers
/// action: arg3 = arg1 - arg2
int op_sub(environment_t *env);

/// code: 0x06
/// coding_byte: yes
/// parameters: arg3 is register, other can be dir-ind or reg
/// action: arg3(reg) = arg1 & arg2
int op_and(environment_t *env);

/// code: 0x07
/// coding_byte: yes
/// parameters: arg3 is register, other can be dir-ind or reg
/// action: arg3(reg) = arg1 | arg2
int op_or(environment_t *env);

/// code: 0x08
/// coding_byte: yes
/// parameters: arg3 is register, other can be dir-ind or reg
/// action: arg3(reg) = arg1 ^ arg2
int op_xor(environment_t *env);

/// code: 0x09
/// coding_byte: no
/// parameters: one index
/// action: jmp to pc + index if carry == 1
int op_zjmp(environment_t *env);

/// code: 0x0a
/// coding_byte:
/// parameters:
/// action:
int op_ldi(environment_t *env);

/// code: 0x0b
/// coding_byte:
/// parameters: 3: one register, and 2 indexes or register
/// action: stores the first arg to PC + (arg2 + arg3) % IDX_MOD
int op_sti(environment_t *env);

/// code: 0x0c
/// coding_byte: no
/// parameters: one index for the new cursos
/// action: duplicate a process with a new cursor
int op_fork(environment_t *env);

/// code: 0x0d
/// coding_byte:
/// parameters:
/// action: ld without %IDX_MOD
int op_lld(environment_t *env);

/// code: 0x0e
/// coding_byte:
/// parameters:
/// action: ldi without %IDX_MOD
int op_lldi(environment_t *env);

/// code: 0x0f
/// coding_byte: no
/// parameters: one new offset index
/// action: fork without %IDX_MOD
int op_lfork(environment_t *env);

/// code: 0x10
/// coding_byte: yes
/// parameters: one register
/// action: prints the ascii character stored in the register
int op_aff(environment_t *env);

#endif /* !VM_H_ */
