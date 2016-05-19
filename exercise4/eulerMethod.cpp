#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

//could be replaced by literal constants; define is the C way
#define K 1
#define M 1
#define H 0.01
#define STEPS 1000
//some constants regarding x_0 and v_0
#define X_0 0
#define V_0 2

double computeNextForce(double x_n_1){

	return -1 * K * x_n_1;

}

double computeNextVelocity(double v_n_1, double F_n){

	return v_n_1 + H / M * F_n;

}

double computeNextPosition(double x_n_1, double v_n_1){

	return x_n_1 + H * v_n_1;

}

int main(int argc, char* argv[]){

	double x_n_1 = X_0;
	double v_n_1 = V_0;
	double f_n = 0;
	std::ofstream eulerFile;

	if(argc == 2){

		eulerFile.open(argv[1], std::ios::out);

	}else{

		std::cout << "Wrong number of arguments.\n\n Useage: prog outfile" << '\n';
		return 1;

	}

	int i = 1;
	for(i = 1; i <= STEPS; i++){

		f_n = computeNextForce(x_n_1);
		double v_n_temp = computeNextVelocity(v_n_1, f_n);
		double x_n_temp = computeNextPosition(x_n_1, v_n_1);

		v_n_1 = v_n_temp;
		x_n_1 = x_n_temp;

		eulerFile << i * H << ' ' << f_n  << ' ' << v_n_1 << ' ' << x_n_1 << '\n';

	}

	eulerFile.close();

}