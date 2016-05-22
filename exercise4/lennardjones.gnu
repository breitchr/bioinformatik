# Gnuplot script file for plotting lennard jones potential and force
set   autoscale                      # scale axes automatically
unset log                            # remove any log-scaling
unset label                          # remove any previous labels
set xtic auto                        # set xtics automatically
set ytic auto                        # set ytics automatically

set title "Lennard-Jones potential and approximation"
set xlabel "r"
set ylabel "V(r)"
   
set xrange [11:13]
set yrange [-3:0]

LJV(x) = 2.0*((12.0/x)**12.0-2.0*(12.0/x)**6.0) 
V(x) = -2.0 + (6.0*2.0)/(12.0**2.0)*(13.0-7.0)*(x-12.0)**2.0

set multiplot layout 1,2 
set size 1,0.5
set origin 0,0

plot V(x) title "Approximation close to equilibrium point", LJV(x) title "Lennard-Jones Potential"

#set term png
#set output "LennardJones.png"
#replot
#set term x11

# o.b.d.A. vector r = |r|*(1,0,0)
# only in x direction because gnuplot does not 

LJF(x) = 12.0*2.0/x * ((12.0/x)**12.0 - (12.0/x)**6.0)
F(x) = -72.0*(x-12.0)/(12.0**2.0)
   
set title "Lennard-Jones force and approximation"
set xlabel "x"
set ylabel "F(x)"

set xrange [10:15]
set yrange [-20:20]
   
set size 1,0.5
set origin 0,0.5
plot F(x) title "Approximation close to equilibrium point", LJF(x) title "Lennard-Jones Force"

unset multiplot
