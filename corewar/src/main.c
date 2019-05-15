/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main for vm
*/

#include "my.h"
#include "vm.h"

int main(int argc, char *argv[])
{
    environment_t *env = read_parameters(argc, argv);
    int lol = 0b10 | 0b01 | 0b11 | 0b01;

    if (env == NULL)
        return (ERROR);
    printf("%x\n", GET_BITS(lol, 0));
    printf("%x\n", GET_BITS(lol, 1));
    printf("%x\n", GET_BITS(lol, 2));
    printf("%x\n", GET_BITS(lol, 3));
    if (load_champions(env) == ERROR)
        return (ERROR);
    if (run_vm(env) == ERROR)
        return (ERROR);
    return (0);
}