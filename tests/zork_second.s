#
# zork.s for corewar
#
# Bob Bylan
#
# Sat Nov 10 03:24;30 2081
#
.name "zork_first"
.comment "just the first instruction of zork"

sti r1, %:live, %1
and r1, %0, r1
