/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main for vm
*/

#include "my.h"
#include "vm.h"

int main(int argc, char **argv)
{
    environment_t *env = read_parameters(argc, argv);

    if (env == NULL)
        return (ERROR);
    return (0);
}
