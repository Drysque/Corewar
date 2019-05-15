/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** corewar
*/

#include "vm.h"
#include "my.h"
#include "asm.h"

int get_list_len(process_t *head)
{
    int len = 0;

    for (; head != NULL; head = head->next)
        len += 1;
    printf("\nLIST LEN %d\n\n", len);
    return (len);
}

static void write_in_arena(unsigned char *arena, unsigned long address, int fd, int size)
{
    char buffer[size];

    if (read(fd, &buffer, size) < size)
        my_error("\tInvalid prog_size\n");
    for (int i = 0; i < size; i += 1)
        arena[address + i] = buffer[i];
    close(fd);
}

int load_champions(environment_t *env)
{
    int division = 0;
    int offset = 0;

    for (process_t *tail = PROC_HEAD(env); tail != NULL; tail = tail->next) {
        if (read(tail->fd, &tail->header, sizeof(header_t)) < (ssize_t)sizeof(header_t))
            my_error("\n\tInvalid header size\n\n");
        tail->header.prog_size = get_no_endian(tail->header.prog_size, 4);
        if (tail->header.prog_size <= 0)
            my_error("\n\tInvalid prog_size\n\n");
        if (get_no_endian(tail->header.magic, 4) != COREWAR_EXEC_MAGIC)
            my_error("\n\tFile is not an executable\n\n");
    }
    division = (int)(MEM_SIZE / get_list_len(env->processes_head));
    printf("DIVISION => %d\n", division);
    for (process_t *tail = PROC_HEAD(env); tail != NULL; tail = tail->next) {
        tail->address = offset;
        printf("\tPROG SIZE %d\n", tail->header.prog_size);
        if (tail->address + division < tail->address + tail->header.prog_size) {
            printf("SET OFFSET TO ADDRESS + PROG_SIZE\n");
            offset = tail->address + tail->header.prog_size;
        } else {
            offset += division;
            offset %= MEM_SIZE;
        }
        printf("ADDRESS: %lu, offset: %d\n", tail->address, offset);
        write_in_arena(env->arena, tail->address, tail->fd, tail->header.prog_size);
    }
    for (int i = 0; i < MEM_SIZE; i += 1)
        printf("%s%02x\e[0m", env->arena[i] ? "\e[1m\e[31m" : "\e[90m", env->arena[i]);
    return (0);
}
