#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include "defines.h"
#include "deriv.h"

using std::vector;
using std::cout;
using std::cin;
using std::endl;


////// Problem definition //////
Vector xy = { 0,0,0};

Vector fun(Vector xy) {
	double x = xy.get_n()[0];
	double y = xy.get_n()[1];
	return Vector({ x*x - 4,y - 1 });
}
////// Problem definition //////


Vector(*funct)(Vector)=fun;
void asknum(Vector &x);
void printnums(const Vector & xy);
bool check(const Vector & xy, Vector(*funct)(Vector));


int main() {
	if (check(xy, funct) == 1) {
		Vector gradient;
		bool limited = 0;
		printnums(xy);
		//asknum(xy);

		for (int i = 0; i < NITMAX; i++) {
			cout << "I am at " << xy;
			gradient = deriv(funct, xy, 4).inv()*fun(xy);
			if (isnan(gradient) || abs(gradient)>LIMITER) {
				gradient = (gradient > 0) ? LIMITER : -LIMITER;
				//gradient = deriv(funct, xy+1, 4).inv()*fun(xy+1);
				limited = 1;
			}
			xy = xy - gradient;
			cout << " and I went to " << xy << " using gradient " << gradient << endl;
			if (limited == 1) { cout << "GRADIENT LIMITED!" << endl; limited = 0; }
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

bool check(const Vector& xy, Vector(*funct)(Vector)) {
		if (xy.len() != funct(xy).len()){
			cout << "Error! Problem is not well defined"<<endl;
			return 0;
	}
		else return 1;
	
}