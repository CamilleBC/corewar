.name "bite"
.comment "chatte"

start:
	live %0
	ld %10, r0
	add r1, r2, r1
	st r1, 3
	lld %:start, r5
