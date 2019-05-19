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
#include "my.h"

static const char *hexdump =
"0000000 ea00 f383 634f 6f74 7262 2065 6f52 6775\n"
"0000010 2065 3456 322e 0000 0000 0000 0000 0000\n"
"0000020 0000 0000 0000 0000 0000 0000 0000 0000\n"
"*\n"
"0000080 0000 0000 0000 0000 0000 6102 6e41 2064\n"
"0000090 6874 2065 6977 6e6e 7265 6920 2073 2e2e\n"
"00000a0 002e 0000 0000 0000 0000 0000 0000 0000\n"
"00000b0 0000 0000 0000 0000 0000 0000 0000 0000\n"
"*\n"
"0000890 7003 0001 0213 0090 0000 0f00 000c 0906\n"
"00008a0 8c01 0001 0000 0c2a 8401 ff09 01f8 0000\n"
"00008b0 2a00 000c 0317 0170 0d00 9002 0000 0000\n"
"00008c0 010f 0000 2a00 ff09 01fb 0000 2a00 000c\n"
"00008d0 0317 0170 0d00 9002 0000 0000 010f 0000\n"
"00008e0 2a00 ff09 01fb 0000 2a00 000c 0317 0170\n"
"00008f0 0d00 9002 0000 0000 010f 0000 2a00 ff09\n"
"0000900 01fb 0000 2a00 ff0c 03a7 0170 0d00 9002\n"
"0000910 0000 0000 010f 0000 2a00 ff09 01fb 0000\n"
"0000920 2a00 7003 fe08 0370 0870 70fe 7003 fe08\n"
"0000930 0370 0870 70fe 7003 fe08 0370 0870 70fe\n"
"0000940 7003 fe08 0370 0870 70fe 7003 fe08 0370\n"
"0000950 0870 70fe 7003 fe08 0370 0870 70fe 7003\n"
"0000960 fe08 0370 0870 70fe 7003 fe08 0370 0870\n"
"0000970 70fe 7003 fe08 0370 0870 70fe 7003 fe08\n"
"0000980 0370 0870 70fe 7003 fe08 0370 0870 70fe\n"
"0000990 7003 fe08 0370 0870 70fe 7003 fe08 0370\n"
"00009a0 0870 70fe 7003 fe08 0370 0870 70fe 7003\n"
"00009b0 fe08 0370 0870 70fe 7003 fe08 0370 0870\n"
"00009c0 70fe 7003 fe08 0370 0870 70fe 7003 fe08\n"
"00009d0 0370 0870 70fe 7003 fe08 0370 0870 70fe\n"
"00009e0 7003 fe08 0370 0870 70fe 7003 fe08 0370\n"
"00009f0 0870 70fe 7003 fe08 0370 0870 70fe 7003\n"
"0000a00 fe08 0370 0870 70fe 7003 fe08 0370 0870\n"
"0000a10 70fe 7003 fe08 0370 0870 70fe 7003 fe08\n"
"0000a20 0270 0090 0000 0f00 fe09 01f5 0000 2a00\n"
"0000a30 000c 012b 0000 2a00 000c 0152 0000 2a00\n"
"0000a40 000c 0278 0390 0370 0300 9002 0313 0670\n"
"0000a50 0206 0090 0000 0f00 0009 018a 0000 2a00\n"
"0000a60 ff0c 01cb 0000 2a00 fe0c 0245 0f90 7003\n"
"0000a70 0306 9002 0317 0670 0206 0090 0000 0f00\n"
"0000a80 9002 0000 0000 090f 5b00 0001 0000 0c2a\n"
"0000a90 8efe 9002 ffff 4201 0203 1a90 7003 0606\n"
"0000aa0 9002 0000 0000 020f 0090 0000 0f00 9002\n"
"0000ab0 0000 0000 090f 2d00 5003 0301 9002 030f\n"
"0000ac0 0670 0206 0090 0000 0f00 9002 0000 0000\n"
"0000ad0 020f 0090 0000 0f00 9002 0000 0000 090f\n"
"0000ae0 0300 7003 0003 030f 0670 ffff 0001 0000\n"
"0000af0 002a                                   \n"
"0000af1\n";

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(testing_asm, get_name_and_comment)
{
    int fd = open("tests/bill.s", O_RDONLY);
    header_t *header = my_calloc((sizeof(header_t)));
    char *name = get_name_and_comment(fd, header);

    cr_assert_str_eq(name, "\tsti r1, %:live, %1");
}

Test(testing_asm, get_no_endian)
{
    cr_assert_eq(get_no_endian(1000, 2), 59395);
    cr_assert_eq(get_no_endian(1000, 4), -402456576);
    cr_assert_eq(get_no_endian(1000, 8), 1000);
}

Test(testing_asm, add_need_label)
{
    op_need_label_t *test = add_need_label("test_label",
    ADD, 0b10, offset_pos(0, GET));

    cr_assert_str_eq("test_label", test->label);
    cr_assert_eq(test->size, DIR_SIZE);
    test = add_need_label("test_label", ADD, 0b100, offset_pos(0, GET));
    cr_assert_eq(test->size, IND_SIZE);
}

Test(testing_asm, test_output_1, .init = redirect_all_std)
{
    compile(open("./tests/Octobre_Rouge_V4.2.s", O_RDONLY), "U_test.cor");
    system("hexdump U_test.cor");
    cr_assert_stdout_eq_str(hexdump);
    system("rm -fr U_test.cor");
}
