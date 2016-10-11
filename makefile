build:
	mkdir plots
	mkdir data
	g++ -o dynEHL main.cpp
	./dynEHL
	gnuplot -e "filename = 'data/data100.dat'; filename2 = 'plots/plot100.png' " gpl.p  
