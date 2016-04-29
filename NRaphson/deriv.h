#pragma once
#include "defines.h"
//Epsilon for differentiation
#define EPSILON 1e-5
//Definition of deriv functions
double deriv(double(*funct)(double),double, int);
Matrix deriv(Vector(*funct)(Vector), Vector, int);
