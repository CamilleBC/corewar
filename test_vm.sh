#!/usr/bin/env bash
us_corewar=corewar
zaz_corewar=resources/corewar

for ((count=100; count < 10000; count += 100))
do
	./$us_corewar -d $count $1 $2 > us
	./$zaz_corewar -d $count $1 $2 > zaz
	sed '1,3d' zaz > tmp; mv tmp zaz
	colordiff us zaz
	if [ $? != 0 ]; then
		echo "Error on cycle $count"
		break
	fi
done
rm zaz us
