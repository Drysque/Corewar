/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** aff instruction
*/

#include "vm.h"
#include "op.h"
#include "my.h"

int op_aff(unsigned char *arena, process_t *proc)
{
    int index = INDEX(arena, proc);
    char coding_byte = (arena[(proc->address + proc->pc + 1) % MEM_SIZE]);

    if (index != 0x10 || coding_byte !=
    (0b01 << 6 | 0b00 << 4 | 0b00 << 2 | 0b00))
        return (1);
    my_printf("%d\n", (proc->registers[(proc->address
    + proc->pc + 2) % MEM_SIZE][0]) % 256);
}