set   autoscale                        #scale axes automatically
unset log                              #remove any log-scaling
unset label                            #remove any previous labels
unset key
set view map scale 1
set xtic auto                          #set xtics automatically
set ytic auto                          #set ytics automatically

set palette defined ( 0 "#f0f0f0",\
                      1 "#bdbdbd",\
                      2 "#636363")
set term png			       #png format
set output filename2		       #output into file
splot filename matrix with image       #create plot
set term x11			       #back to terminal (Linux only?)
