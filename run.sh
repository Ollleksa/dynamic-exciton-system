#!/bin/bash

echo "It will destroy all old data (if possible). Agreed? (n for not):"
read check;
if [ ${check} == 'n' ];
then
	exit 0
fi

if [ -d data ];
then
	rm -r data
fi
mkdir data

if [ -d plot ];
then
	rm -r plot
fi
mkdir plot

g++ -o dynEHL main.cpp
./dynEHL

numfiles=(data/*)
numfiles=${#numfiles[@]}
 
for (( i=1; i<=${numfiles}; i++ ));
do
	gnuplot -e "filename = 'data/data${i}00.dat'; filename2 = 'plot/plot${i}.png' " gpl.p
done

ffmpeg -framerate 2  -i 'plot/plot%d.png'  -c:v libx264 out.mp4
