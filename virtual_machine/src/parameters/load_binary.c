/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** load binary
*/

#include "vm.h"
#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "op.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int read_header(int fd)
{
    op_t op;
    header_t header;
    char coding_byte;

    if (read(fd, &header, sizeof(header_t)) == -1)
        return (ERROR);
    if (read(fd, &op.mnemonique, sizeof(char *) != sizeof(char *)))
        return (ERROR);
    if (read(fd, &op.nbr_args, sizeof(char)) != sizeof(char))
        return (ERROR);
    if (read(fd, &op.type, sizeof(char) * MAX_ARGS_NUMBER) != sizeof(char) * MAX_ARGS_NUMBER)
        return (ERROR);
    if (read(fd, &op.code, sizeof(char)) != sizeof(char))
        return (ERROR);
    if (read(fd, &coding_byte, sizeof(char)) != sizeof(char))
        return (ERROR);
    if (read(fd, &op.nbr_cycles, sizeof(int)) != sizeof(int))
        return (ERROR);
    if (read(fd, &op.comment, sizeof(char *)) != sizeof(char *))
        return (ERROR);
    close(fd);
    return (0);
}

static int load_binary(const char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    int status = 0;

    if (fd == -1) {
        write(2, "Cannot open file\n", 17);
        return;
    }
    status = read_header(fd);
    if (status == ERROR)
        return (ERROR);
    return (0);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (ERROR);
    return load_binary(argv[1]);
}
