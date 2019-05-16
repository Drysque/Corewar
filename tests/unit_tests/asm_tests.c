/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** asm_tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "asm.h"
#include "vm.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}