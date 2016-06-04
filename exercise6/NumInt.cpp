#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {

  double k = 1.0;
  double m = 1.0;
  double h = 0.01;
  
  // double h = 0.01; does not affect the simulation in the range of t = 40
  // greater timessteps lead to a divergence of the Ekin and Pges especially for the euler method
  
  ofstream euler;
  ofstream verlet;
  euler.open("euler.txt");
  verlet.open("verlet.txt");
  
  euler << "t Ekin Pges" << endl;
  verlet << "t Ekin Pges" << endl;

  double t0 = 0.0;

  vector<double> eulerx;
  vector<double> eulerv;
  vector<double> eulerF;

  vector<double> verletx;
  vector<double> verletv;
  vector<double> verletF;

  eulerx.push_back(1.0);
  eulerv.push_back(1.0);
  eulerF.push_back(0);

  verletx.push_back(1.0);
  verletv.push_back(1.0);
  verletF.push_back(0);

  for(int n=1;n<10000;n++){
    eulerx.push_back(eulerx[n-1] + h*eulerv[n-1]);
    eulerF.push_back(-k*eulerx[n-1]);
    eulerv.push_back(eulerv[n-1] + h/m*eulerF[n]);

    verletx.push_back(verletx[n-1]+verletv[n-1]*h+verletF[n]/(2*m)*pow(h,2));
    verletF.push_back(-k*verletx[n]);
    verletv.push_back(verletv[n-1] + h/(2*m)*(verletF[n-1] + verletF[n]));
  }
  
  for(int n=0;n<10000;n++){
    euler << t0+n*h << " " << 3/2*m*pow(eulerv[n],2) << " " << 3*m*eulerv[n] << endl;
    verlet << t0+n*h << " " << 3/2*m*pow(verletv[n],2) << " " << 3*m*verletv[n] << endl;
  }

  euler.close();
  verlet.close();

  system("gnuplot plot.gnu");
  
  return 0;
}

