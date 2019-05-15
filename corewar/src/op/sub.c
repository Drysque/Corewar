/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** sub instruction
*/

#include "vm.h"
#include "op.h"

int op_sub(unsigned char *arena, process_t *proc)
{
    int index = INDEX(arena, proc);
    char coding_byte = (arena[(proc->address + proc->pc + 1) % MEM_SIZE]);

    if (index != 0x05 || coding_byte !=
    (0b01 << 6 | 0b01 << 4 | 0b01 << 2 | 0b00))
        return (1);
    proc->registers[(proc->address + proc->pc + 4) % MEM_SIZE][0] =
    (proc->address + proc->pc + 2) - (proc->address + proc->pc + 3);
}