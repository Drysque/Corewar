/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** lib prototypes
*/

#ifndef MY_H_
#define MY_H_

#include <stddef.h>
#include <stdbool.h>

int my_getnbr(char const *str);
char my_str_to_char(char const *str);
char my_str_to_int16(char const *str);

int my_strlen(char const *str);
int my_tablen(char const **tab);

void my_printf(char *str, ...);
void my_putchar(char c);
int my_putstr(char const *str);

char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strdup(char const *src);
char *my_strndup(char const *src);
char *my_strcat(char *buffer, char *str);

bool my_strcmp(char const *s1, char const *s2);
bool my_strncmp(char const *s1, char const *s2, int n);
int my_strcmp_diff(char const *s1, char const *s2);

void *my_calloc(size_t size);

char *get_next_line(int fd);
char **my_str_delim_array(char const *str, char *delims);

#endif /* MY_H_ */
