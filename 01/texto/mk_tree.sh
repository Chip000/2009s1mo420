#!/bin/sh
# This script generates the missing dirs for the project

IMG_DIR=$2;

echo ">>> Making dir";

if [[ -e $IMG_DIR ]]
then
    echo ">>> $IMG_DIR is ready :P";
else
    echo ">>> Creating $IMG_DIR";
    mkdir $IMG_DIR;
fi;

echo ">>> End";

# EOF
