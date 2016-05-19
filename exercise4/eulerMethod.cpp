#include <string>


//could be replaced by literal constants; define is the C way
#define K 1
#define M 1
#define H 0.01



double computeNextForce(double x_n_1){

	return -1 * K * x_n_1;

}

double computeNextVelocity(double v_n_1, double F_n){

	return v_n_1 * H/M * F_n;

}

double computeNextPosition(double x_n_1, double v_n_1){

	return x_n_1 + H * v_n_1

}