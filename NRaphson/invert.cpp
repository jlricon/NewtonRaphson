#include "invert.h"

Matrix invert(const Matrix & mat)
{
	
	double a[mat.get_rows()][mat.get_cols()];
	double d;
	int i, j, k, n;
	n = mat.get_rows();
	
	/************** partial pivoting **************/
	for (i = n; i>1; i--)
	{
		if (a[i - 1][1]<a[i][1])
			for (j = 1; j <= n * 2; j++)
			{
				d = a[i][j];
				a[i][j] = a[i - 1][j];
				a[i - 1][j] = d;
			}
	}

	/********** reducing to diagonal  matrix ***********/

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n * 2; j++)
			if (j != i)
			{
				d = a[j][i] / a[i][i];
				for (k = 1; k <= n * 2; k++)
					a[j][k] -= a[i][k] * d;
			}
	}
	/************** reducing to unit matrix *************/
	for (i = 1; i <= n; i++)
	{
		d = a[i][i];
		for (j = 1; j <= n * 2; j++)
			a[i][j] = a[i][j] / d;
	}
	// Assign to matrix
	Matrix ret(n,n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			ret.assign(i, j, a[i][j]);
		}
	}
	return ret;
}

