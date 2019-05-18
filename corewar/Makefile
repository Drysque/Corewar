##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile Corewar VirtualMachine
##

SHELL		=	sh

CC			=	gcc

AR_RC		=	ar rc

RM			=	rm -f

SRCDIR		=	./src

SRC			=	$(SRCDIR)/main.c							\
				../asm/src/get_no_endian.c					\
				../include/op.c								\
				$(SRCDIR)/parameters/get_parameters.c		\
				$(SRCDIR)/core/load_champions.c				\
				$(SRCDIR)/core/run_vm.c						\
				$(SRCDIR)/op/live.c								\
				$(SRCDIR)/op/ld.c								\
				$(SRCDIR)/op/st.c								\
				$(SRCDIR)/op/add.c								\
				$(SRCDIR)/op/sub.c								\
				$(SRCDIR)/op/and.c								\
				$(SRCDIR)/op/or.c								\
				$(SRCDIR)/op/xor.c								\
				$(SRCDIR)/op/zjmp.c								\
				$(SRCDIR)/op/ldi.c								\
				$(SRCDIR)/op/sti.c								\
				$(SRCDIR)/op/fork.c								\
				$(SRCDIR)/op/lld.c								\
				$(SRCDIR)/op/lldi.c								\
				$(SRCDIR)/op/lfork.c							\
				$(SRCDIR)/op/aff.c								\

OBJ			=	$(SRC:.c=.o)

CPPFLAGS	=	-iquote ../include/ -Wall -Wextra

LDFLAGS		=	-L../lib/my

LDLIBS		=	-lmy

DEBUGFLAGS	=	-g3

NAME		=	corewar

all: 			$(NAME)

$(NAME): 		$(OBJ)
				$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

debug:
				$(CC) -o $(NAME) $(SRC) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) $(DEBUGFLAGS)

clean:
				@$(RM) $(OBJ)

fclean: 		clean
				@$(RM) $(NAME)

re: 			fclean all

.PHONY:			debug clean fclean re all
