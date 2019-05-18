/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main for vm
*/

#include "my.h"
#include "vm.h"

static void display_help(void)
{
    my_printf("USAGE\n");
    my_printf("\t./corewar[-dump nbr_cycle][[-n prog_number]"
    "[-a load_address] prog_name]...\n");
    my_printf("DESCRIPTION\n");
    my_printf("\t-dump nbr_cycle\tdumps the memory after the"
    "nbr_cycle execution");
    my_printf("\t(if the round isn’t\n\talready over) with the"
    "following format : 32 bytes / line in\n\thexadecimal(A0BCDEFE1DD3...)\n");
    my_printf("\n\t-n prog_numbersets the next program’s number."
    "By default,the first free number\n\tin the parameter order\n");
    my_printf("\n\t-a load_addresssets the next program’s loading address."
    "When no address is\n\tspecified, optimize the addresses so that the "
    "processes are as far\n\taway from each other as possible.The addresses"
    "are MEM_SIZE modulo.\n");
}

int main(int argc, char **argv)
{
    environment_t *env = NULL;
    int lol = 0b10 | 0b01 | 0b11 | 0b01;

    if (argc == 1) {
        my_printf("Usage: ./corewar [-g] [-dump cycle_nb] [[-a load_addr] [-n prog_nb] prog.cor] ...\n");
        return (84);
    }
    if (argc == 2 && my_strcmp("-h", argv[1]) == true) {
        display_help();
        return (0);
    }
    env = read_parameters(argc, argv);
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