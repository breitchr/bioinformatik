#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

/* v is fixed, calculation of v(t+1/2dt) not necessary
double vplus(double t, double dt){
  if (t <= 0){
    return 1.0;
  }
  else {
    return vplus(t-1/2*dt,dt) + dt*(f(t)-chi(t)*v(t,dt));
  }
}
*/
double v(double t, double dt, double fixed){
  if (t <= 0){
    return 1.0;
  }
  else {
    // fix velocity to 0.8 or 1.2
    return fixed;  //1/2*(v(t-1/2*dt,dt)+v(t+1/2*dt,dt));
  }
}

// x(t) for a harmonic oszillator with m=k=1
double x(double t){
  
  double x0 = 1.0;
    
  if(t == 0){
    return x0;
  }
  else {
    return (x0*cos(t));
  }
  
}

double x(double t, double dt, double fixedv){
  return (x(t) + dt*v(t,dt,fixedv));
}

int main(int argc, char* argv[]) {

  ofstream outfile1;
  ofstream outfile2;
  outfile1.open("NoseHooverOut08.txt");
  outfile2.open("NoseHooverOut12.txt");
  
  outfile1 << "t x(t) v(t)" << endl;
  outfile2 << "t x(t) v(t)" << endl;
  double dt = 0.1;
  
  for (double t = 0; t < stod(argv[1]); t+=dt){
    outfile1 << t << "  " << x(t, dt, 0.8) << "  " << v(t, dt, 0.8) << endl;
    outfile2 << t << "  " << x(t, dt, 1.2) << "  " << v(t, dt, 1.2) << endl;
    
  }
  
  outfile1.close();
  outfile2.close();

  // plot x(t) and v(t)
  system("gnuplot plot.gnu ");
 
  return 0;
}

