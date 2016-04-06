#pragma once
#include "defines.h"
double deriv(double(*funct)(double),double, int);
Matrix deriv(Vector(*funct)(Vector), Vector, int);
