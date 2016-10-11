build:
	g++ -o dynEHL main.cpp
	./dynEHL
	mkdir plots
	gnuplot -e "filename = 'data100.dat'; filename2 = 'plots/plot100.png' " gpl.p  
