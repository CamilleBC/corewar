.name "Koko"
.comment "Il aime bien les abricots et faire des calins a sa peluche"

start:
	st r1, -0
	ld -5, r1
	ld %507, r2
	fork %:p2

p1:
	ld %190055170, r3
	ld %0, r4
	zjmp %:write

p2:
	ld -7, r4
	ld 27, r3
	xor r8,r8,r8
	zjmp %:write

write:
	st r1, 6
	live %0
	sti r3, r2, r4
	zjmp %502
