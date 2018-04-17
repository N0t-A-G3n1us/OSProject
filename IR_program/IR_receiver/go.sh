#!/bin/sh

PROG=$1
TS=$2
echo " i'm doing cleaning ! @@_/"
make clean

if [ "$PROG" != "" ]; then
	if [ "$TS" != "test" ]; then
		make PROG_NAME=$PROG TEST_FLAG=0 && make PROG_NAME=$PROG program
	else
		make PROG_NAME=$PROG TEST_FLAG=1 && make PROG_NAME=$PROG program
	fi
else 
	echo 'usage: <name_of_file_without_extension> ["test"]'
fi
