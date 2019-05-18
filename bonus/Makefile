##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

SHELL	=	/bin/sh

NAME	=	corewar_gui

CC		?=	gcc

RM		?= 	rm -f

SRC =	src/main.c

CSFML_LIB	=	-lcsfml-system -lcsfml-graphics -lcsfml-window  -lcsfml-audio

CPPFLAGS	=	-iquote./includes

CFLAGS		+=	-Wall -Wextra

LDFLAGS	=	 -lm

LDLIBS	=	-lm $(CSFML_LIB)

OBJ	=	$(SRC:.c=.o)

all: $(NAME)

debug: CFLAGS += -g3
debug: re

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJ)
	$(RM) *~
	$(RM) vgcore*


fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: fclean clean debug re all sign
