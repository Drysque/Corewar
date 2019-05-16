##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile Corewar
##

SHELL		=	sh

MAKE		=	make

COMPILERDIR	=	./asm

VMDIR		=	./corewar

LIBDIR		=	./lib/my

TESTDIR		=	./tests/unit_tests

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
			$(MAKE) clean -C $(TESTDIR)

fclean:
			$(MAKE) fclean -C $(LIBDIR)
			$(MAKE) fclean -C $(COMPILERDIR)
			$(MAKE) fclean -C $(VMDIR)
			$(MAKE) fclean -C $(TESTDIR)

tests_run:
			$(MAKE) tests_run -C $(TESTDIR)
			./unit_test

re: fclean all

.PHONY: debug clean fclean re all
