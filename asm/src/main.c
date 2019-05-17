/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main for asm
*/

#include "my.h"
#include "asm.h"

static void check_args(int ac, char const *av[])
{
    char *help = "USAGE\n\t%s file_name[.s]\n"
    "DESCRIPTION\n\n"
    "\tfile_name\tfile in assembly language "
    "to be converted into file_name.cor, an\n"
    "\t\t\texecutable in the Virtual Machine.\n";

    if (ac != 2 || my_strcmp(av[1], "-h") || my_strcmp(av[1], "--help")) {
        my_printf(help, av[0]);
        exit(84);
    }
}

static char *check_file(char const *file, int *fd)
{
    char *dup;
    char *dup_cor;

    *fd = open(file, O_RDONLY);
    if (*fd < 0) {
        my_printf("\n\t\e[1m\e[31mCould not open file:\e[0m %s\n\n", file);
        return NULL;
    }
    dup = my_strdup(file);
    if (dup == NULL)
        my_error("Out of memory");
    for (size_t i = my_strlen(dup) - 1; i > 0; i--)
        if (dup[i] == '.') {
            dup[i] = '\0';
            break;
        }
    dup_cor = my_strcat(dup, ".cor");
    free(dup);
    return dup_cor;
}

int main(int ac, char const *av[])
{
    char *name = NULL;
    int fd = 0;

    check_args(ac, av);
    name = check_file(av[1], &fd);
    if (name == NULL)
        return 84;
    compile(fd, name);
    free(name);
    close(fd);
    return 0;
}
