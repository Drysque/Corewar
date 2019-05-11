/*
** EPITECH PROJECT, 2019
** compile.c
** File description:
** starts the compilation
*/

#include "asm.h"
#include "my.h"

static const char NO_CODING_BYTE[] = {0x01, 0x09, 0x0c, 0x0f, 0x0};
static const char NO_DIRECT_SIZE[] = {0x05, 0x09, 0x0b, 0x0c, 0x0};

static void get_direct_indirect(op_list_t *op, char **instr_tab, int i)
{
    if (instr_tab[i][0] == '%') {
        op->type[i] = 0b10;
        if (is_one_of_them(op->code, NO_DIRECT_SIZE))
            op->true_type[i] = 0b11;
        else
            op->true_type[i] = 0b10;
        // op->true_type[i] = is_one_of_them(op->code, NO_DIRECT_SIZE) ? 0b11 : 0b10;
        if (instr_tab[i][1] == LABEL_CHAR)
            add_need_label(&instr_tab[i][2], ADD, op->true_type[i], op->begin_offset);
        else
            op->args[i] = my_getnbr(&instr_tab[i][1]);
        offset_pos(op->true_type[i] == 0b10 ? DIR_SIZE : IND_SIZE, ADD); // printf("added offset of %d for dir/indir\n", op->true_type[i] == 2 ? 4 : 2);
    }
    else {
        op->type[i] = 0b11;
        op->true_type[i] = 0b11;
        op->args[i] = my_getnbr(instr_tab[i]);
        offset_pos(IND_SIZE, ADD);
        // printf("added offset of 2 for indirect\n");
    }
}

void get_args_type(op_list_t *op, char **instr_tab)
{
    for (int i = 0; instr_tab[i]; i++) {
        if (instr_tab[i][0] == 'r') {
            op->type[i] = 0b01;
            op->true_type[i] = 0b01;
            op->args[i] = my_getnbr(&instr_tab[i][1]);
            offset_pos(1, ADD);// printf("added offset of 1 for register\n");
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
    new_op->begin_offset = offset_pos(0, GET);
    clean_arguments(&instr_tab[1]);
    for (int i = 0; op_tab[i].mnemonique != 0; i++) {
        if (my_strcmp(op_tab[i].mnemonique, instr_tab[0])) {
            new_op->code = op_tab[i].code;
            offset_pos(1, ADD);
            if (is_one_of_them(op_tab[i].code, NO_CODING_BYTE) == false)
                offset_pos(1, ADD);
            if (my_tablen((char const **)&instr_tab[1]) != op_tab[i].nbr_args) {
                my_printf("wrong number of arguments for instruction %s (%d)\n",
                    instr_tab[0], my_tablen((char const **)&instr_tab[1]));
                exit(84);
            }
            get_args_type(new_op, &instr_tab[1]);
            new_op->next_op = *op_list;
            *op_list = new_op;
            printf("total bytes theorically written: \e[1m\e[32m%d\e[0m (%d)\n", offset_pos(0, GET) + sizeof(header_t), offset_pos(0, GET));
            return;
        }
    }
    my_printf("unknown instruction %s\n", instr_tab[0]);
    exit(84);
}

static void add_label(char *label_name, label_t **label_list)
{
    label_t *new_label = my_calloc(sizeof(label_t));

    new_label->name = label_name;
    new_label->offset = offset_pos(0, GET);
    // printf("(added label %s: %d)\n", new_label->name, new_label->offset);
    new_label->next_label = *label_list;
    *label_list = new_label;
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
    else
        add_instruction(tab, op_list);
}

static void print_op(op_list_t *instruction_list, int fd)
{
    char type = 0;
    int swapped = 0;

    if (instruction_list == NULL)
        return;
    print_op(instruction_list->next_op, fd);
    // printf("wrote instruction %x at %d of size 1\n", instruction_list->code, lseek(fd, 0, SEEK_CUR));
    write(fd, &instruction_list->code, 1);
    printf("wrote instruction %x of size \e[1m\e[33m%d\e[0m\n", instruction_list->code, 1);
    for (int i = 0; i < MAX_ARGS_NUMBER; i++)
        type |= instruction_list->type[i] << (2 * (MAX_ARGS_NUMBER - 1 - i));
    if (is_one_of_them(instruction_list->code, NO_CODING_BYTE) == false) {
        printf("wrote type %x of size \e[1m\e[33m%d\e[0m\n", type, 1);
        write(fd, &type, 1);
    }
    for (int i = 0; i < MAX_ARGS_NUMBER && instruction_list->type[i]; i++) {
        switch (instruction_list->true_type[i]) {
        case 1: swapped = instruction_list->args[i];
            // printf("1 byte: not swapped: %x\n", swapped);
            printf("wrote %d of size \e[1m\e[33m%d\e[0m\n", get_no_endian(swapped, 1), 1);
            write(fd, &swapped, 1);
            break;
        case 2: swapped = get_no_endian(instruction_list->args[i], DIR_SIZE);
            // printf("4 bytes: swapped: %x\n", swapped);
            printf("wrote %d of size \e[1m\e[33m%d\e[0m\n", get_no_endian(swapped, DIR_SIZE), DIR_SIZE);
            write(fd, &swapped, DIR_SIZE);
            break;
        case 3: swapped = get_no_endian(instruction_list->args[i], IND_SIZE);
            // printf("2 bytes: swapped: %x\n", swapped);
            printf("wrote %d of size \e[1m\e[33m%d\e[0m\n", get_no_endian(swapped, IND_SIZE), IND_SIZE);
            write(fd, &swapped, IND_SIZE);
            break;
        default: break;
        }
    }
    printf("total bytes actually written: \e[1m\e[32m%d\e[0m\n", lseek(fd, 0, SEEK_CUR));
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
    printf("total bytes actually written: \e[1m\e[32m%d\e[0m\n", lseek(fd, 0, SEEK_CUR));
    write(fd, header, sizeof(header_t));
    printf("printing header\ntotal bytes actually written: \e[1m\e[32m%d\e[0m\n\n", lseek(fd, 0, SEEK_CUR));
    print_op(op_list, fd);

    fill_needed_label(fd, label_list);
    header->magic = get_no_endian(COREWAR_EXEC_MAGIC, 4);
    printf("total written: %d\n", lseek(fd, 0, SEEK_END));
    header->prog_size = get_no_endian(offset_pos(0, GET), 4);
    lseek(fd, 0, SEEK_SET);
    write(fd, header, sizeof(header_t));
    close(fd);
    // printf("name: {%s}, comment {%s}\n", header->prog_name, header->comment);
}

void compile(int fd, char *new_file)
{
    char *str;
    header_t *header = my_calloc(sizeof(header_t));
    label_t *label_list = NULL;
    op_list_t *op_list = NULL;

    printf("\ntotal bytes theorically written: \e[1m\e[32m%d\e[0m (%d)\n", offset_pos(0, GET) + sizeof(header_t), offset_pos(0, GET));
    while ((str = get_next_instruction(fd)) != NULL) {
        printf("\ninstruction found: {\e[1m\e[34m%s\e[0m}\n", str);
        parse_instruction(str, &label_list, &op_list, header);
        free(str);
    }
    /**/
    // op_need_label_t *list = add_need_label(NULL, GET, 0, 0);
    // while (list) {
    //     printf("\noffset of instruction need label: %d", list->offset + sizeof(header_t));
    //     list = list->next_op;
    // }
    /**/
    printf("\n------------BEGINNING WRITING-----------\n\n");
    write_in_file(header, label_list, op_list, new_file);
}
