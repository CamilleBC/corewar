.name "bite"
.comment "chatte"

start:
	ld %-1, r1
	ld %-3, r3
	st r1, r2
	st r3, 100
	sti r1, %0, %4
	ld %4, r4
	ld %5, r5
	fork %1
	add r4, r5, r6
	sub r6, r5, r7
	live %0
<<<<<<< HEAD
	zjmp %:start
=======
	fork %10
>>>>>>> d9fe8bb52e650b4a11e49d5c96a795a1605d5d00
