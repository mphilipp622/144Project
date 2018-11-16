#!/bin/sh
make;
printf "\n";

for i in 1 5 10
do
	for j in 1 5 10
	do
		./myapp.exe "$i" "$j" &
	done
done