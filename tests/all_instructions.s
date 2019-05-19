.name "mega test"
.comment "hehehe"

live:
    live %-1
    live %0
    live %1

ld:
    ld %-1, r1
    ld %0, r1
    ld %1, r1

    ld -1, r1
    ld 0, r1
    ld 1, r1

st:
    st r1, -1
    st r1, 0
    st r1, 1

    st r16, r16

add:
    add r1, r8, r16
    add r3, r4, r5
    add r16, r8, r1

sub:
    sub r1, r8, r16
    sub r3, r4, r5
    sub r16, r8, r1

and:
    and r16, r15, r13
    and r7, -8, r10
    and r4, %-90, r3

    and %1, r1, r6
    and %1, %1, r1
    and %1, -14, r01

    and 1, r12, r1
    and -10, %1, r1
    and -201, 1, r1

or:
    or r16, r15, r13
    or r7, -8, r10
    or r4, %-90, r3

    or %1, r1, r6
    or %1, %1, r1
    or %1, -14, r01

    or 1, r12, r1
    or -10, %1, r1
    or -201, 1, r1

xor:
    xor r16, r15, r13
    xor r7, -8, r10
    xor r4, %-90, r3

    xor %1, r1, r6
    xor %1, %1, r1
    xor %1, -14, r01

    xor 1, r12, r1
    xor -10, %1, r1
    xor -201, 1, r1

zjmp:
    zjmp %-1
    zjmp %0
    zjmp %1

ldi:
    ldi r16, r15, r13
    ldi r4, %-90, r3

    ldi %1, r1, r6
    ldi %1, %1, r1

    ldi 1, r12, r1
    ldi -10, %1, r1

sti:
    sti r1, r1, r1
    sti r1, r1, %1

    sti r1, %1, r1
    sti r1, %1, %1

    sti r1, 1, r1
    sti r1, 1, %1

fork:
    fork %-1
    fork %0
    fork %1

lld:
    lld %1, r1
    lld 1, r1

lldi:
    lldi r1, %1, r1
    lldi r1, r1, r1

    lldi %1, %1, r1
    lldi %1, r1, r1

    lldi 1, %1, r1
    lldi 1, r1, r1

lfork:
    lfork %-1
    lfork %0
    lfork %1

aff:
    aff r1
    aff r2
    aff r3
    aff r4
    aff r5
    aff r6
    aff r7
    aff r8
    aff r9
    aff r10
    aff r11
    aff r12
    aff r13
    aff r14
    aff r15
    aff r16
