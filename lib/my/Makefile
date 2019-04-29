##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile for my_printf
##

CC		=	gcc

AR_RC	=	ar rc

RM     =	rm -f

NAME	=	libmy.a

SRC		=	my_printf.c				\
			format_switches.c		\
			get_next_line.c			\
			my_getnbr.c				\
			my_put_long_base.c		\
			my_put_long_unsigned.c	\
			my_put_nbr_base.c		\
			my_put_nbr_long.c		\
			my_put_nbr_pos.c		\
			my_put_nbr_space.c		\
			my_put_nbr.c			\
			my_put_ptr.c			\
			my_put_unsigned.c		\
			my_putchar.c			\
			my_putstr_non_print.c	\
			my_putstr.c				\
			my_str_delim_array.c	\
			my_str_isnum.c			\
			my_strcat.c				\
			my_strcmp.c				\
			my_strcpy.c				\
			my_strdup.c				\
			my_strlen.c				\
			my_strncpy.c			\
			my_strndup.c			\
			my_tablen.c				\
			switch_flags.c			\

OBJ	=		$(SRC:.c=.o)

all:		$(NAME)

$(NAME):
			$(CC) -c $(SRC)
			$(AR_RC) $(NAME) $(OBJ)

debug:		fclean
			@gcc -c $(SRC) -g3
			@$(AR_RC) $(NAME) *.o

clean:
			@$(RM) $(OBJ)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all
