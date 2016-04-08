#include "deriv.h"
#include "defines.h"

//Differentiation of non-vectors
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
//Differentiation of vectors for any size
Matrix deriv(Vector(*funct)(Vector), Vector xy, int order = 1) {
	Matrix result(xy.len(), xy.len());
	Vector hm1 = xy;
	Vector hm2 = xy;
	Vector col;
	//Calculate one column
	for (int i = 0; i < xy.len(); i++) {
		
		hm1.assign(i, xy.get_n()[i] + EPSILON);
		hm2.assign(i, xy.get_n()[i] - EPSILON);
		col = (funct(hm1) - funct(hm2)) / (2 * EPSILON);
		for (int j = 0; j < xy.len(); j++) {
			result.assign(j, i, col.get_n()[j]);
		}
		hm1.assign(i, xy.get_n()[i]);
		hm2.assign(i, xy.get_n()[i]);

	}
	return result;
	
	
	
}

