#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include "defines.h"
#include "deriv.h"

//Max number of iterations for NR
#define NITMAX 100
//Accuracy for NR
#define TOL 1e-5
//Max gradient allowed
#define LIMITER 1e4

using std::vector;
using std::cout;
using std::cin;
using std::endl;


////// Problem definition //////
Vector xy = {1,1,1};

Vector fun(Vector xy) {
	double x = xy.get_n()[0];
	double y = xy.get_n()[1];
	double z = xy.get_n()[2];
	
	return Vector({2*z-3*z*z+1,x-3*z+y-3*z*y,2*z-6*y+3*y*y});
}
////// Problem definition //////

// Declare functions that are defined later 
Vector(*funct)(Vector)=fun;
void asknum(Vector &x);
void printnums(const Vector & xy);
bool check(const Vector & xy, Vector(*funct)(Vector));


int main() {
	//If you want to input your own values for xy
	//asknum(xy);

	if (check(xy, funct) == 1) {
		Vector gradient;
		bool limited = 0;
		//Print the numbers around the starting point
		printnums(xy);		
		//Main loop
		for (int i = 0; i < NITMAX; i++) {
			cout << "I am at " << xy<<endl;
			//Gradient calculation G=Jac^-1*f(x)
			gradient = deriv(funct, xy, 4).inv()*fun(xy);
			//Gradient limiter. In case the Jacobian has det=0, limit the gradient
			if (isnan(gradient) || abs(gradient)>LIMITER) {
				gradient = (gradient > 0) ? LIMITER : -LIMITER;
				limited = 1;
			}
			xy = xy - gradient;
			//cout << " and I went to " << xy << " using gradient " << gradient << endl;
			//Say if the gradient has been limited
			if (limited == 1) { cout << "GRADIENT LIMITED!" << endl; limited = 0; }
			//Check convergence. All values of the function must be smaller than TOL
			if (abs(fun(xy)) < TOL) {
				cout << "Converged. Function is zero at: " << xy << endl;
				break;
			}
		}
		system("pause");
		return 0;
	}
	
	else { system("pause"); return EXIT_FAILURE; }
}




//Ask for starting point
void asknum(Vector &v) {
	double input;
	bool flag = 0;
	std::string line;
	cout << "Please enter starting point: ";
	getline(cin, line);
	std::istringstream iss(line);
	while (iss >> input) {
		v.get_np()->push_back(input);
	}
	
}

//Print numbers near 0
void printnums(const Vector& xy) {
	double h;
	Vector n=xy;
	cout << "hvalue " << "Values when only x is nonzero" << endl;
	for (int i = 0; i <= 10; i++) {
		h = 0.1* double(i);
		n.assign(0, h);
		cout << h << "  " << fun(n)<< endl;
	}
}
//Check that the initial conditions and the equation system are coherent
bool check(const Vector& xy, Vector(*funct)(Vector)) {
		if (xy.len() != funct(xy).len()){
			cout << "Error! Problem is not well defined"<<endl;
			return 0;
	}
		else return 1;
	
}