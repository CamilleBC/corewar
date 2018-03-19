.name "bite"
.comment "chatte"

start:
	ld %-1, r1
	ld %-3, r3
	st r1, r2
	st r3, 100
	sti r1, %0, %4
st:
	ld %4, r4
	ld %5, r5
	add r4, r5, r6
	sub r6, r5, r7
	live %0
	fork %10
