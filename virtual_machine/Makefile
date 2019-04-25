##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile Corewar VirtualMachine
##

SH			=	sh

CC			=	gcc

AR_RC		=	ar rc

RM			=	rm -f

SRC			=	\

OBJ			=	$(SRC:.c=.o)

CPPFLAGS	=	-I./include/

DEBUGFLAGS	=	-g3 -Wall -Wextra

NAME		=	corewar

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

debug:
	$(CC) -o $(NAME) $(SRC) $(CPPFLAGS) $(DEBUGFLAGS)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: debug clean fclean re all
