# gnuplot script to plot Nose-Hoover output
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set title "Simulation of a harmonic oszillator with fixed velocity"
set xlabel "t"
set ylabel "x(t), v(t)"
set xr [0.0:100]
set yr [-2:2]


set size 2,2
set origin 0,0
set multiplot layout 2,1 columnsfirst scale 1,1

plot "NoseHooverOut08.txt" using 1:3 title 'v(t) fixed to 0.8' with linespoints, "NoseHooverOut08.txt" using 1:2 title 'x(t)' with linespoints

plot "NoseHooverOut12.txt" using 1:3 title 'v(t) fixed to 1.2' with linespoints, "NoseHooverOut12.txt" using 1:2 title 'x(t)' with linespoints

unset multiplot