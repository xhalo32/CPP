#!/bin/bash

for x in {4..64}
do
	printf $x': '$( bc <<< "2^$x-1" )' '
	bc <<< 'scale=2; '$(echo $(./factors $(echo "2^$x-1" | bc) "-q") | rev | cut -d" " -f 1 | rev)'/'$x'-1/'$x
done