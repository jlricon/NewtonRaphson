#pragma once
#include "defines.h"

//Definition of deriv functions
double deriv(double(*funct)(double),double, int);
Matrix deriv(Vector(*funct)(Vector), Vector, int);
