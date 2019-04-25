/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** lib prototypes
*/

#ifndef MY_H_
#define MY_H_

int my_getnbr(char const *str);
int my_strlen(char const *str);

void my_printf(char *str, ...);
void my_putchar(char c);
int my_putstr(char const *str);

char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char const *src, int n);
char *my_strdup(char const *src);
char *my_strcat(char *buffer, char *str);

int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
int my_strcmp_diff(char const *s1, char const *s2);

char **my_str_delim_array(char const *str, char *delims);

#endif /* MY_H_ */
