#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include "defines.h"


using std::vector;
using std::endl;
using std::cout;
using std::cin;



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
		cout << " and I went to " << in<<" using gradient "<<gradient<<endl;
		if (limited == 1) { std::cout << "GRADIENT LIMITED!" << endl; limited = 0; }
		if (abs(funct(in)) < TOL) {
			cout << "Converged. Function is zero at: " << in<<endl;
			break;
		}
	}
	system("pause");
		return 0;
}

double funct(double x) {
	return x*x-16;

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
		cout << "Please enter starting point: ";
		if (cin >> x) {
			// valid number
			break;
		}
		else {
			// not a valid number
			cout << "Invalid Input! Please input a numerical value." << endl;
			cin.clear();
			while (std::cin.get() != '\n'); // empty loop
		}
	}
}

void printnums() {
	double h;
	cout << "Instant " << " Value " << "Derivative" << endl;
	for (int i = 0; i < 10; i++) {
		h = 0.1* double(i);
		cout << h << "  " << funct(h) << " " << deriv(h, 4) << endl;
	}
}