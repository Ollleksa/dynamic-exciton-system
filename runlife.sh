#!/bin/bash

#echo "It will destroy all old data (if possible). Agreed? (n for not):"
#read check;
#if [ ${check} == 'n' ];
#then
#	exit 0
#fi

if [ -d life ];
then
	rm -r life
fi
mkdir life

if [ -d plotlife ];
then
	rm -r plotlife
fi
mkdir plotlife

g++ -o liferun life.cpp
./liferun

numfiles=(life/*)
numfiles=${#numfiles[@]}
 
for (( i=1; i<=${numfiles}; i++ ));
do
	gnuplot -e "filename = 'life/data${i}.dat'; filename2 = 'plotlife/plot${i}.png' " gpl.p
done

ffmpeg -framerate 8  -i 'plotlife/plot%d.png'  -c:v libx264 lifev2.mp4
