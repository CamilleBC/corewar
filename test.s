.name "bite"
.comment "chatte"

start:
ld %100000000000, r1
ld %-3, r3
st r1, r2
st r3, 100
sti r1, %0, %4
ld %4, r4
ld %5, r5
add r4, r5, r6
sub r6, r5, r7
zjmp %0
