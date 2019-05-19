##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile Corewar
##

SHELL		=	sh

MAKE		=	make

RM			=	rm -f

COMPILERDIR	=	./asm

VMDIR		=	./corewar

LIBDIR		=	./lib/my/

TESTDIR		=	./tests/unit_tests

TESTSRC		=	$(TESTDIR)/asm_tests.c						\
				./include/op.c								\
				$(COMPILERDIR)/src/add_instruction.c		\
				$(COMPILERDIR)/src/add_needed_label.c		\
				$(COMPILERDIR)/src/compile.c				\
				$(COMPILERDIR)/src/fill_needed_label.c		\
				$(COMPILERDIR)/src/free_all.c				\
				$(COMPILERDIR)/src/get_args_type.c			\
				$(COMPILERDIR)/src/get_name_and_comment.c	\
				$(COMPILERDIR)/src/get_next_instruction.c	\
				$(COMPILERDIR)/src/get_no_endian.c			\
				$(COMPILERDIR)/src/offset_manage.c			\
				$(COMPILERDIR)/src/parse_instruction.c		\
				$(COMPILERDIR)/src/remove_quotes.c			\
				$(COMPILERDIR)/src/write_in_file.c			\

all:
			$(MAKE) -C $(LIBDIR)
			$(MAKE) -C $(COMPILERDIR)
			$(MAKE) -C $(VMDIR)

debug:
			$(MAKE) debug -C $(LIBDIR)
			$(MAKE) debug -C $(COMPILERDIR)
			$(MAKE) debug -C $(VMDIR)

clean:
			$(MAKE) clean -C $(LIBDIR)
			$(MAKE) clean -C $(COMPILERDIR)
			$(MAKE) clean -C $(VMDIR)

fclean:		clean
			$(MAKE) fclean -C $(LIBDIR)
			$(MAKE) fclean -C $(COMPILERDIR)
			$(MAKE) fclean -C $(VMDIR)
			@$(RM) *.gc*
			@$(RM) ./unit_tests

tests_run:
			$(MAKE) -C $(LIBDIR)
			$(CC) -o unit_tests $(TESTSRC) -iquote./include/ -L$(LIBDIR)\
				-lmy -lcriterion --coverage
			./unit_tests

re: fclean all

.PHONY: debug clean fclean re all
