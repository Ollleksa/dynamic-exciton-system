
# Gnuplot script file for plotting data in file "data[iter].txt"
set   autoscale                        #scale axes automatically
unset log                              #remove any log-scaling
unset label                            #remove any previous labels
unset key
set view map scale 1
set xtic auto                          #set xtics automatically
set ytic auto                          #set ytics automatically
set contour base
set cntrparam levels discrete 1, 5, 10
set style data lines
unset surface

#filename(n) = sprintf("data%d00.dat", n)

#      splot for [i=1:3] filename(i) matrix with lines
splot filename matrix with lines

set term png
set output filename2
replot
set term x11
