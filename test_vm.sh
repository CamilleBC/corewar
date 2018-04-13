#!/usr/bin/env bash
us_corewar=corewar
zaz_corewar=resources/corewar

for ((count=3000; count < 10000; count++))
do
	./$us_corewar -d $count $1 $2 > us
	./$zaz_corewar -d $count $1 $2 > zaz
	sed -n '/^0x0000/,$p' zaz > tmp; mv tmp zaz
	diff us zaz
	if [ $? != 0 ]; then
		echo "Error on cycle $count"
		break
	fi
	echo $count
done
