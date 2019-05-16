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
    int a = 0b10 << 6 | 0b11 << 4 | 0b01 << 2 | 0b00;
    if (env == NULL)
        return (ERROR);
    printf("%d\n", GET_BITS(a, 0));
    printf("%d\n", GET_BITS(a, 1));
    printf("%d\n", GET_BITS(a, 2));
    printf("%d\n", GET_BITS(a, 3));
    if (load_champions(env) == ERROR)
        return (ERROR);
    if (run_vm(env) == ERROR)
        return (ERROR);
    return (0);
}