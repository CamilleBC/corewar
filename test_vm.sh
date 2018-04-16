#!/usr/bin/env bash
us_corewar=corewar
zaz_corewar=resources/corewar
add=1000
sub=-10
error=0
to_end=0

echo "comparing vms..."
for ((count=1000; count < 10000; count += add))
do
	./$us_corewar -d $count $@ > us
	./$zaz_corewar -d $count $@ > zaz
	sed -n '/^0x0000/,$p' zaz > tmp; mv tmp zaz
	diff zaz us &> log
	#wdiff --no-common zaz us
	if [[ $? != 0 ]]; then
		if [[ $to_end == 1 ]]; then
			# phase 3: we have found the smallest cycle
			echo cycle: $count
			cat log | colordiff
			break
		fi
		# phase 1: we found error so we go backward
		error=$(($error + 1))
		add=$(($error * $sub))
	elif [[ $error > 0 ]]; then
		# phase 2: no we go
		add=1
		to_end=1
	fi
done
rm zaz us log
