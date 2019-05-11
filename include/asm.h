/*
** EPITECH PROJECT, 2019
** asm.h
** File description:
** header for the compiler
*/

#ifndef ASM_H_
#define ASM_H_

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include "op.h"

/* TO REMOVE */ #include <stdio.h> //TO REMOVE

enum {
    GET,
    ADD,
    SUB,
};

typedef struct op_need_label_s {
    off_t offset;
    char *label;
    off_t begin_offset;
    int size;
    struct op_need_label_s *next_op;
} op_need_label_t;

typedef struct op_list_s {
    char code;
    off_t begin_offset;
    args_type_t type[MAX_ARGS_NUMBER];
    args_type_t true_type[MAX_ARGS_NUMBER];
    int args[MAX_ARGS_NUMBER];
    struct op_list_s *next_op;
} op_list_t;

typedef struct label_s {
    char *name;
    off_t offset;
    struct label_s *next_label;
} label_t;

char *get_next_instruction(int fd);
int get_no_endian(int nb, int size);
void compile(int fd, char *new_file);
off_t offset_pos(ssize_t written, int status);
void fill_needed_label(int fd, label_t *label_list);
bool add_name_or_comment(char *instruction, header_t *header);
void add_instruction(char **instruction_tab, op_list_t **op_list);
op_need_label_t *add_need_label(char *name, int status,
    int size, off_t begin_offset);
void write_in_file(header_t *header, label_t *label_list,
    op_list_t *op_list, char *new_file);
void parse_instruction(char *instruction, label_t **label_list,
    op_list_t **op_list, header_t *header);

#endif /* ASM_H_ */
