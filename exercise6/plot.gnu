# gnuplot script to plot Nose-Hoover output
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set xlabel "t"
set ylabel "Ekin(t), Pges(t)"


set size 2,2
set origin 0,0
set multiplot layout 2,1 columnsfirst scale 1,1

set xr [0.0:20.0]
set yr [-20:20]
set title "Numerical integration - harmonic oscillator - Euler algorithm"
plot "euler.txt" using 1:2 title 'Ekin(t)' with points, "euler.txt" using 1:3 title 'Pges(t)' with points

set xr [0.0:20.0]
set yr [-20:20]
set title "Numerical integration - harmonic oscillator - Velocity-Verlet algorithm"
plot "verlet.txt" using 1:2 title 'Ekin(t)' with points, "verlet.txt" using 1:3 title 'Pges(t)' with points

unset multiplot