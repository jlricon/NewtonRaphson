#include "invert.h"
#include "defines.h"
#include <iostream>
#include <algorithm>

//From http://users.ices.utexas.edu/~alen/articles/mat-inv-rep.pdf

double getR(const Matrix &a);
Matrix invert(const Matrix & mat)
{
	unsigned i;
	double R = getR(mat);
	Matrix X=(1/(2*R))*mat.tr();
	int n = mat.get_rows();
	Matrix I(n, n);
	for (i = 0; i < n; i++) {
		I.assign(i, i, 1);
	}
	Matrix I2(5*I);
	Matrix I3(3*I);
	Matrix I4 = I2*I3;
	for (i = 0; i <100; i++) {
		X = (X*(2 * I - mat*X));
	
	}

	return X;
}

//Calculate R
double getR(const Matrix &a) {
	Matrix b = a*a.tr();
	double n1 = 0, n2 = 0;
	//Now we sum the columns
	for (unsigned i = 0; i < a.get_rows(); i++) {
		for (unsigned j = 0; j < a.get_cols(); j++) {
			n1 += b(i, j);
		}
		n2 = std::max(n1, n2);
		n1 = 0;
	}
	return n2;
}

