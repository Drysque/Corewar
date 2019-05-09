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
        my_printf("\e[1m\e[31m%s: no such file\e[0m\n", file);
        return NULL;
    }
    dup = my_strdup(file);
    for (size_t i = my_strlen(dup) - 1; i > 0; i--)
        if (dup[i] == '.')
            dup[i] = '\0';
    dup_cor = my_strcat(dup, ".cor");
    free(dup);
    return dup_cor;
}

static void add_label(char *label_name, label_t **label_list)
{
    label_t *new_label = my_calloc(sizeof(label_t));

    new_label->name = label_name;
    // new_label->offset = offset_pos(0, GET);
    new_label->next_label = *label_list;
    *label_list = new_label;
}

bool add_name_or_comment(char *instruction, header_t *header)
{
    int index = 0;
    int i = 0;

    for (; instruction[index] != '\0' &&
    (instruction[index] == ' ' || instruction[index] == '\t'); index += 1);
    if (instruction[index] == '\0')
        return false;
    if (my_strncmp(&instruction[index], NAME_CMD_STRING, my_strlen(NAME_CMD_STRING)))
        index += my_strlen(NAME_CMD_STRING);
    else if (my_strncmp(&instruction[index], COMMENT_CMD_STRING, my_strlen(COMMENT_CMD_STRING))) {
        index += my_strlen(COMMENT_CMD_STRING);
        i = 1;
    } else
            return false;
    for (; instruction[index] != '\0' &&
    (instruction[index] == ' ' || instruction[index] == '\t'); index += 1);
    if (instruction[index] == '\0')
        return false;
    if (instruction[index] == '\"') {
        index += 1;
        for (int len = my_strlen(instruction) - 1; len > 0; len--)
            if (instruction[len] == '\"') {
                instruction[len] = 0;
                break;
            }
    }
    if (i == 0)
        my_strcpy(header->prog_name, &instruction[index]);
    else
        my_strcpy(header->comment, &instruction[index]);
    return true;
}

void get_direct_indirect(op_list_t *op, char **instr_tab, int i)
{
    char code_tab[2] = {11, 9};

        if (instr_tab[i][0] == '%') {
            op->type[i] = 0b10;
            for (int j = 0; j < 2; j += 1)
                if (op->code == code_tab[j]) {
                    op->true_type[i] = 0b11;
                    offset_pos(2, ADD);
                    break;
                } else if (j + 1 == 2) {
                    op->true_type[i] = 0b10;
                    offset_pos(4, ADD);
                }
            if (instr_tab[i][1] == LABEL_CHAR) {
                add_need_label(&instr_tab[i][2], ADD);
            } else
                op->args[i] = my_getnbr(&instr_tab[i][1]);
            // my_printf("0x00 0x00 0x00 0x%x ", my_getnbr(&instr_tab[i][1]));
        }
        else {
            op->type[i] = 0b11;
            op->true_type[i] = 0b11;
            op->args[i] = my_getnbr(instr_tab[i]);
            offset_pos(2, ADD);
            // my_printf("0x00 0x%x ", my_getnbr(instr_tab[i]));
        }
}

void get_args_type(op_list_t *op, char **instr_tab)
{
    for (int i = 0; instr_tab[i]; i++) {
        if (instr_tab[i][0] == 'r') {
            op->type[i] = 0b01;
            op->true_type[i] = 0b01;
            op->args[i] = my_getnbr(&instr_tab[i][1]);
            offset_pos(1, ADD);
            // my_printf("0x%x ", my_getnbr(&instr_tab[i][1]));
        } else
           get_direct_indirect(op, instr_tab, i);
    }
}

static void clean_arguments(char **instr_tab)
{
    int len;

    for (int i = 0; instr_tab && instr_tab[i]; i++) {
        len = my_strlen(instr_tab[i]) - 1;
        if (instr_tab[i][len] == SEPARATOR_CHAR)
            instr_tab[i][len] = '\0';
    }
}

void add_instruction(char **instr_tab, op_list_t **op_list)
{
    op_list_t *new_op;

    if (instr_tab[0] == NULL)
        return;
    new_op = my_calloc(sizeof(op_list_t));
    clean_arguments(&instr_tab[1]);
    for (int i = 0; op_tab[i].mnemonique != 0; i++) {
        if (my_strcmp(op_tab[i].mnemonique, instr_tab[0])) {
            new_op->code = op_tab[i].code;
            if (i != 0 && i != )/
                offset_pos(1, ADD);

            if (my_tablen((char const **) &instr_tab[1]) != op_tab[i].nbr_args) {
                my_printf("wrong number of arguments for instruction %s (%d)\n",
                    instr_tab[0], my_tablen((char const **) &instr_tab[1]));
                exit(84);
            }
            get_args_type(new_op, &instr_tab[1]);
            new_op->next_op = *op_list;
            *op_list = new_op;
            return;
        }
    }
    my_printf("unknown instruction %s\n", instr_tab[0]);
    exit(84);
}

void parse_instruction(char *instruction, label_t **label_list,
    op_list_t **op_list, header_t *header)
{
    char **tab = my_str_delim_array(instruction, " \t");

    if (tab == NULL) {
        my_printf("instruction failure: {%s}\n", instruction);
        exit(84);
    }
    if (add_name_or_comment(instruction, header));
    else if (tab[0][my_strlen(tab[0]) - 1] == LABEL_CHAR) {
        tab[0][my_strlen(tab[0]) - 1] = 0;
        add_label(tab[0], label_list);
        add_instruction(&tab[1], op_list);
    }
    else {
        add_instruction(tab, op_list);
    }
}

static int get_no_endian(int nb, int size)
{
    // printf("DEBUG in: %x\n", nb);
    // printf("DEBUG out: %x\n", bytes[3] | bytes[2] | bytes[1] | bytes[0]);
    int bytes[] = {(nb & 0xff) << 24, (nb & 0xff00) << 8, (nb & 0xff0000) >> 8, (nb & 0xff000000) >> 24};
    int x = ((nb & 0xff) << 8 | (nb & 0xff00) >> 8);

    printf("BEFORE SWITCH: %x\n", nb);
    switch (size) {
        case 2:
            printf("AFTER 2: %x\n", x);
            return x;
        case 4:
            printf("AFTER 4: %x\n", (bytes[3] | bytes[2] | bytes[1] | bytes[0]));
            return (bytes[3] | bytes[2] | bytes[1] | bytes[0]);
        default: return (nb);
    }
    return (nb);
}

static void print_op(op_list_t *instruction_list, int fd)
{
    char type = 0;
    int swapped = 0;

    if (instruction_list == NULL)
        return;
    print_op(instruction_list->next_op, fd);
    write(fd, &instruction_list->code, sizeof(char));
    printf("instruction code: %d\n", instruction_list->code);
    for (int i = 0; i < MAX_ARGS_NUMBER; i++)
        type |= instruction_list->type[i] << (2 * (MAX_ARGS_NUMBER - 1 - i));
    //if (INSTRUCTION AVEC CODING BYTE);
        write(fd, &type, 1);
    printf("type: %d\n", type);
    for (int i = 0; i < MAX_ARGS_NUMBER && instruction_list->type[i]; i++) {
        switch (instruction_list->true_type[i]) {
        case 1: swapped = instruction_list->args[i];
            printf("1 byte: not swapped: %x\n", swapped);
            write(fd, &swapped, 1);
            break;
        case 2: swapped = get_no_endian(instruction_list->args[i], 4);
            printf("4 bytes: swapped: %x\n", swapped);
            write(fd, &swapped, 4);
            break;
        case 3: swapped = get_no_endian(instruction_list->args[i], 2);
            printf("2 bytes: swapped: %x\n", swapped);
            write(fd, &swapped, 2);
            break;
        default: break;
        }
    }
    printf("\n");
}

void write_in_file(header_t *header, label_t *label_list,
    op_list_t *op_list, char *new_file)
{
    int fd = open(new_file, O_TRUNC | O_CREAT | O_RDWR, 00666);

    if (fd < 0) {
        my_printf("\e[1m\e[31m%s: couldn't create file\e[0m\n", new_file);
        exit(84);
    }
    write(fd, header, sizeof(header_t));
    print_op(op_list, fd);

    //FINAL
    fill_needed_label(fd, label_list);
    header->magic = get_no_endian(COREWAR_EXEC_MAGIC, 4);
    printf("%d\n", (int)offset_pos(0, GET));
    header->prog_size = get_no_endian((int)offset_pos(0, GET), 4);
    lseek(fd, 0, SEEK_SET);
    write(fd, header, sizeof(header_t));
    close(fd);
    my_printf("name: {%s}, comment {%s}\n", header->prog_name, header->comment);
}

void compile(int fd, char *new_file)
{
    char *str;
    header_t *header = my_calloc(sizeof(header_t));
    label_t *label_list = NULL;
    op_list_t *op_list = NULL;

    while ((str = get_next_instruction(fd)) != NULL) {
        my_printf("instruction found: {\e[1m\e[34m%s\e[0m}\n", str);
        parse_instruction(str, &label_list, &op_list, header);
        free(str);
    }
    write_in_file(header, label_list, op_list, new_file);
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
