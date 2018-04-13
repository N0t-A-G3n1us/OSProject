#!/bin/sh

PROG=$1
echo " i'm doing cleaning ! @@_/"
make clean

if [ "$PROG" != "" ]; then
	make PROG_NAME=$PROG && make PROG_NAME=$PROG program
else 
	echo "usage: <name_of_file_without_extension>"
fi
