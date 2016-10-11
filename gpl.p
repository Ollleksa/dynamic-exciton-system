# Gnuplot script file for plotting data in file "data[iter].txt"
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

      splot "data100.txt" using 1:2 matrix with lines
