
# Gnuplot script file for plotting data in file "data[iter].txt"
set   autoscale                        #scale axes automatically
unset log                              #remove any log-scaling
unset label                            #remove any previous labels
unset key
set view map scale 1
set xtic auto                          #set xtics automatically
set ytic auto                          #set ytics automatically
set contour base		       #contour plot
set cntrparam levels discrete 1, 5, 10 #contour levels
set style data lines
unset surface			       #with no surface only contour

#filename(n) = sprintf("data%d00.dat", n)
#splot for [i=1:3] filename(i) matrix with lines		#usefull staff for later usage
#splot filename matrix with lines

set term png			       #png format
set output filename2		       #output into file
splot filename matrix with lines       #create plot
set term x11			       #back to terminal (Linux only?)
