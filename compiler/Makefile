##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile Corewar Compiler
##

SHELL		=	sh

CC			=	gcc

AR_RC		=	ar rc

RM			=	rm -f

SRCDIR		=	./src

SRC			=	$(SRCDIR)/main.c				\
				$(SRCDIR)/compile.c				\
				$(SRCDIR)/get_next_instruction.c\
				$(SRCDIR)/create_header.c		\
				$(SRCDIR)/create_label.c		\
				$(SRCDIR)/parse_instruction.c	\
				$(SRCDIR)/write_in_file.c		\

OBJ			=	$(SRC:.c=.o)

CPPFLAGS	=	-iquote ../include/

LDFLAGS		=	-L../lib/my

LDLIBS		=	-lmy

DEBUGFLAGS	=	-g3 -Wall -Wextra

NAME		=	asm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

debug:
	$(CC) -o $(NAME) $(SRC) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) $(DEBUGFLAGS)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: debug clean fclean re all
