#!/usr/bin/env bash
us_corewar=corewar
zaz_corewar=resources/corewar

for ((count=1; count < 10000; count += 10))
do
	./$us_corewar -d $count $1 $2 > us
	./$zaz_corewar -d $count $1 $2 > zaz
	sed '1,3d' zaz > tmp; mv tmp zaz
	echo $count"-------------------------------------\n"
	diff us zaz
	echo "-------------------------------------------\n"
done
rm zaz us
