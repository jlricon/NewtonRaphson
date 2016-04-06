#include "deriv.h"
#include "defines.h"


double deriv(double (*funct)(double), double h, int order = 4) {

	if (order == 2) {
		return (funct(h + EPSILON) - funct(h - EPSILON)) / (2 * EPSILON);
	}
	else if (order == 4) {
		return (funct(h - 2 * EPSILON) - 8 * funct(h - EPSILON) + 8 * funct(h + EPSILON) - funct(h + 2 * EPSILON)) / (12 * EPSILON);
	}
	else {
		return(funct(h + EPSILON)-funct(h)) / EPSILON;
	}
}
Matrix deriv(Vector(*funct)(Vector), Vector xy, int order = 1) {
	Matrix result(xy.len(), xy.len());
	Vector col1=(funct({ xy.get_n()[0] + EPSILON,xy.get_n()[1] }) - funct({ xy.get_n()[0] - EPSILON,xy.get_n()[1] })) /(2* EPSILON);
	Vector col2 = (funct({ xy.get_n()[0],xy.get_n()[1] + EPSILON }) - funct({ xy.get_n()[0],xy.get_n()[1] - EPSILON })) / (2*EPSILON);
	result.assign(0, 0, col1(0));
	result.assign(1, 0, col1(1));
	result.assign(0, 1, col2(0));
	result.assign(1, 1, col2(1));
	return result;
	
	
	
}

