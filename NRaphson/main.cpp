#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#define EPSILON 1e-6
#define NITMAX 1000
#define TOL 1e-4
#define LIMITER 1e6

double funct(double);
double deriv(double, int);
void asknum(double &x);
void printnums();

int main() {
	double in=0;
	double gradient;
	bool limited=0;
	
	printnums();	
	asknum(in);
	
	for (int i = 0; i < NITMAX; i++) {
		std::cout << "I am at " << in;
		gradient = funct(in) / deriv(in,4);
		if(isnan(gradient) || abs(gradient)>LIMITER){
			gradient = (gradient > 0) ? LIMITER : -LIMITER;
			limited = 1;
			} 
		in = in -gradient;
		std::cout << " and I went to " << in<<" using gradient "<<gradient<<std::endl;
		if (limited == 1) { std::cout << "GRADIENT LIMITED!" << std::endl; limited = 0; }
		if (abs(funct(in)) < TOL) {
			std::cout << "Converged. Function is zero at: " << in<<std::endl;
			break;
		}
	}
		return 0;
}

double funct(double x) {
	double x1 = 1;
	double y = 2;
	std::vector<double> funci = { x1 + y,y - 1 };
	return x*x+x-1;

}

double deriv(double h, int order = 2) {

	if (order == 2) {
		return (funct(h + EPSILON) - funct(h - EPSILON)) / (2 * EPSILON);
	}
	else if (order == 4) {
		return (funct(h - 2 * EPSILON) - 8 * funct(h - EPSILON) + 8 * funct(h + EPSILON) - funct(h + 2 * EPSILON)) / (12 * EPSILON);
	}
	else {
		return(funct(h + EPSILON) / EPSILON);
	}
}
void asknum(double &x) {
	while (1) {
		std::cout << "Please enter starting point: ";
		if (std::cin >> x) {
			// valid number
			break;
		}
		else {
			// not a valid number
			std::cout << "Invalid Input! Please input a numerical value." << std::endl;
			std::cin.clear();
			while (std::cin.get() != '\n'); // empty loop
		}
	}
}

void printnums() {
	double h;
	std::cout << "Instant " << " Value " << "Derivative" << std::endl;
	for (int i = 0; i < 10; i++) {
		h = 0.1* double(i);
		std::cout << h << "  " << funct(h) << " " << deriv(h, 4) << std::endl;
	}
}