#!/usr/bin/env bash
us_corewar=corewar
zaz_corewar=resources/corewar
add=1000

for ((count=1; count < 10000; count += add))
do
	./$us_corewar -d $count $1 $2 > us
	./$zaz_corewar -d $count $1 $2 > zaz
	sed -n '/^0x0000/,$p' zaz > tmp; mv tmp zaz
	colordiff zaz us
	if [ $? != 0 ]; then
		if [ $add == 1 ]; then
			break;
		fi
		count=$(($count - $add))
		add=$(($add / 10))
	fi
	echo $count
done
