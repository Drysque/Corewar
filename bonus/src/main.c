/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main for vm
*/

#include "main.h"

static void display_help(void)
{
    my_printf("GOOD LUCK\n");
}

int main(int argc, char **argv)
{
    environment_t *env = NULL;

    if (argc == 1) {
        my_printf("Usage: ./corewar [-g] [-dump cycle_nb] [[-a load_addr]"
        " [-n prog_nb] prog.cor] ...\n");
        return (84);
    }
    if (argc == 2 && my_strcmp("-h", argv[1])) {
        display_help();
        return (0);
    }
    env = read_parameters(argc, argv);
    if (env == NULL)
        return (ERROR);
    if (load_champions(env) == ERROR)
        return (ERROR);
    if (run_vm_gui(env) == ERROR)
        return (ERROR);
    return (0);
}
