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
				$(SRCDIR)/parameters/get_parameters.c		\

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
