#!/bin/bash

if [ $1 ]
then
	PORT=/dev/ttyUSB$1
	echo  "Port: $PORT"
	BAUD=1500000
	#BAUD=9600
	echo  "Baud: $BAUD"
	fuser -k $PORT
	sudo chmod +666 $PORT
	unbuffer cu -l $PORT -s $BAUD 
else 
	echo "Need a port buddy. Port list:"	
	ls /dev/ttyUSB*

fi
