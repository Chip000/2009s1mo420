#!/bin/sh
# This script runs the program for all instances for given relaxation 

echo ">>> Starting"

for param in $(ls ./parameters/); do
	for infile in $(ls ./inst/); do
		echo "./relaxlag $1 ./inst/$infile ./parameters/$param";
		time ./relaxlag $1 ./inst/$infile ./parameters/$param;
	done;
done;

echo ">>> Ending"