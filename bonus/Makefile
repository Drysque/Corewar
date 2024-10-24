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

SRCDIR	=	../corewar/src

SRC =	src/csfml.c								\
	src/main.c							\
	$(SRCDIR)/parameters/get_parameters.c		\
	$(SRCDIR)/core/load_champions.c				\
	$(SRCDIR)/core/run_vm.c						\
	$(SRCDIR)/core/dump.c						\
	$(SRCDIR)/op/live.c							\
	$(SRCDIR)/op/ld.c							\
	$(SRCDIR)/op/st.c							\
	$(SRCDIR)/op/add.c							\
	$(SRCDIR)/op/sub.c							\
	$(SRCDIR)/op/and.c							\
	$(SRCDIR)/op/or.c							\
	$(SRCDIR)/op/xor.c							\
	$(SRCDIR)/op/zjmp.c							\
	$(SRCDIR)/op/ldi.c							\
	$(SRCDIR)/op/sti.c							\
	$(SRCDIR)/op/fork.c							\
	$(SRCDIR)/op/lld.c							\
	$(SRCDIR)/op/lldi.c							\
	$(SRCDIR)/op/lfork.c						\
	$(SRCDIR)/op/aff.c							\
	../asm/src/get_no_endian.c					\
	../include/op.c

CSFML_LIB	=	-lcsfml-system -lcsfml-graphics -lcsfml-window  -lcsfml-audio

CPPFLAGS	=	-I ./include -I ../corewar/src -I ../include

CFLAGS		+=	-Wall -Wextra

LDFLAGS	=	 -L../lib/my

LDLIBS	=	-lm $(CSFML_LIB) -lmy

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
