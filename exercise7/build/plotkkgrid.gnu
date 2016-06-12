# gnuplot script to plot katchalski katzir output

set parametric 
set contour base 
set view 0,0,1
unset surface
set cntrparam levels 5
set dgrid3d

set title "Katchalski-Katzir Grid entries for different planes"

set size 2,2
set origin 0,0
set multiplot layout 3,1 columnsfirst scale 1,1

set xr [-10.0:10.0]
set yr [-10.0:10.0]
set zr [0:2]
set xlabel "x"
set ylabel "y"
splot "kkgrid.txt" using 1:2:4 title "x-y plane" with line

set xr [-10.0:10.0]
set yr [-10.0:10.0]
set zr [0:2]
set xlabel "y"
set ylabel "z"
plot "kkgrid.txt" using 2:3:4 title "y-z plane" with line

set xr [-10.0:10.0]
set yr [-10.0:10.0]
set zr [0:2]
set xlabel "x"
set ylabel "z"
plot "kkgrid.txt" using 1:3:4 title "x-z plane" with line

unset multiplot