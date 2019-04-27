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
    op_t *op;
    struct op_list_s *next_op;
} op_list_t;

typedef struct label_s {
    char *name;
    op_list_t *instruction_list;
    struct label_s *next_label;
} label_t;

void compile(int fd);
header_t *create_header(int fd);
label_t *create_label(char *name);
char *get_next_instruction(int fd);
void write_in_file(header_t *header, label_t *label_list);
void parse_instruction(char *instruction, label_t **label_list);

#endif /* ASM_H_ */
