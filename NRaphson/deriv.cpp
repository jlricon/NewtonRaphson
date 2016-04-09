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
Matrix deriv(Vector(*funct)(Vector), Vector xy, int order = 2) {
	Matrix result(xy.len(), xy.len());
	Vector hm1 = xy;
	Vector hm2 = xy;
	Vector col;
	if (order == 2) {
		//Second order method
		for (unsigned i = 0; i < xy.len(); i++) {

			hm1.assign(i, xy(i) + EPSILON);
			hm2.assign(i, xy(i) - EPSILON);
			col = (funct(hm1) - funct(hm2)) / (2 * EPSILON);
			for (unsigned j = 0; j < xy.len(); j++)result.assign(j, i, col(j));
			hm1.assign(i, xy(i));
			hm2.assign(i, xy(i));
		}
	}
	else if (order == 4) {
		//Fourth order method
		Vector hm3=xy;
		Vector hm4=xy;
		for (unsigned i = 0; i < xy.len(); i++) {
			hm1.assign(i, xy(i) + 2*EPSILON);
			hm2.assign(i, xy(i) - 2*EPSILON);
			hm3.assign(i, xy(i) + EPSILON);
			hm4.assign(i, xy(i) - EPSILON);
			col = (funct(hm2) - 8*funct(hm4)+8*funct(hm3)-funct(hm1)) / (12 * EPSILON);
			for (unsigned j = 0; j < xy.len(); j++)	result.assign(j, i, col(j));
			hm1.assign(i, xy(i));
			hm2.assign(i, xy(i));
			hm3.assign(i, xy(i));
			hm4.assign(i, xy(i));
		}

	}
	else {
		for (unsigned i = 0; i < xy.len(); i++) {
			//First order method
			hm2.assign(i, xy(i) - EPSILON);
			col = (funct(xy) - funct(hm2)) / (EPSILON);
			for (unsigned j = 0; j < xy.len(); j++)	result.assign(j, i, col(j));
			hm1.assign(i, xy(i));
			
		}
	}
	return result;
	}
	


