#!/bin/sh
# This script generates the missing dirs for the project

# OBJ_DIR is in Makefile
OBJ_DIR=$(grep "^ODIR" Makefile | cut -f 2 -d "=");

# OUT_DIR is in src/main.c
OUT_DIR=$(grep "#define GNUPLOT_DIR" src/main.c | sed -ne 's/.*"\(.*\)".*/\1/p');

echo ">>> Making dirs";

for i in {$OBJ_DIR,$OUT_DIR}
do
    if [[ -e $i ]]
    then
	echo ">> $i is ready :P";
    else
	echo ">> Creating $i";
	mkdir $i;
    fi
done;

echo ">>> End";

# EOF