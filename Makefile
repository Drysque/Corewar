##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile Corewar
##

SH			=	sh

MAKE		=	make

COMPILERDIR	=	./compiler

VMDIR	=	./virtual_machine

all:
	$(MAKE) -C $(COMPILERDIR)
	$(MAKE) -C $(VMRDIR)

debug:
	$(MAKE) debug -C $(COMPILERDIR)
	$(MAKE) debug -C $(VMRDIR)

clean:
	$(MAKE) clean -C $(COMPILERDIR)
	$(MAKE) clean -C $(VMRDIR)

fclean:
	$(MAKE) fclean -C $(COMPILERDIR)
	$(MAKE) fclean -C $(VMRDIR)

re: fclean all

.PHONY: debug clean fclean re all
