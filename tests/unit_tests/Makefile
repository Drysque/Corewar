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

SRCDIR		=	../../asm/src

SRC			=	$(SRCDIR)/main.c					\
				$(SRCDIR)/add_instruction.c			\
				$(SRCDIR)/add_needed_label.c		\
				$(SRCDIR)/compile.c					\
				$(SRCDIR)/fill_needed_label.c		\
				$(SRCDIR)/get_args_type.c			\
				$(SRCDIR)/get_name_and_comment.c	\
				$(SRCDIR)/get_next_instruction.c	\
				$(SRCDIR)/get_no_endian.c			\
				$(SRCDIR)/offset_manage.c			\
				$(SRCDIR)/parse_instruction.c		\
				$(SRCDIR)/write_in_file.c			\
				../../include/op.c					\

CPPFLAGS	=	-iquote ../../include/

LDFLAGS		=	-L../../lib/my

LDLIBS		=	-lmy

DEBUGFLAGS	=	-g3 -Wall -Wextra

NAME		=	unit_test

tests_run:
				make -C ../../lib/my
				$(CC) -o $(NAME) $(SRC) $(LDFLAGS) $(LDLIBS) $(CPPFLAGS) \
				-lcriterion --coverage
				mv $(NAME) ../..

clean:
				make clean -C ../../lib/my
				@$(RM) *.gc*

fclean: 		clean
				make fclean -C ../../lib/my
				@$(RM) ../..$(NAME)

re: 			fclean all

.PHONY:			debug clean fclean re all
