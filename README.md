# dynamic-exciton-system
Simple evolution problem with exitons and electron-hole liquid. Model is far from ideal, so results are almost useless.
Files: main.cpp - create matrixes with data about system, had most information about it;
       gpl.p - gnuplot script, which created image of system for every data.
       run.sh - bash script, which run main.cpp and gpl.p in right order. And created directories for data and plots
       
In basis of this program, build Game of Life model (https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life). It works. But looks like shit. And you need gpl.p for it.
Files: life.cpp - program itself
       runlife.sh - bash script which create nice videos
