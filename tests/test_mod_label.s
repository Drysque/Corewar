#
# test.s for corewar
#
# Bob Bylan
#
# Sat Nov 10 03:24;30 2081
#
.name "test"
.comment "just a basic test"

l2: sti r20, %99, 50
    and r30, %40, 50
live: live %60
    zjmp %99
