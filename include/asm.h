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
#include "op.h"

typedef struct op_list_s {
    char code;
    args_type_t type[MAX_ARGS_NUMBER];
    // char args[MAX_ARGS_NUMBER];
    void *args[MAX_ARGS_NUMBER];
    struct op_list_s *next_op;
} op_list_t;

typedef struct label_s {
    char *name;
    op_list_t *instruction_list;
    struct label_s *next_label;
} label_t;

header_t *create_header(int fd);
label_t *create_label(char *name);
char *get_next_instruction(int fd);
void compile(int fd, char *new_file);
void parse_instruction(char *instruction, label_t **label_list);
void add_instruction(char **instruction_tab, op_list_t **op_list);
void write_in_file(header_t *header, label_t *label_list, char *new_file);

#endif /* ASM_H_ */
