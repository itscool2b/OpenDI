#include "calculus/secondderivative.h"
#include "calculus/centraldiff.h"
#include <math.h>

double (double (*f)(double), double x, double h){

    if (h == 0.0){

    return NAN;
    }

    return (f(x+h) - (2*f(x)) + f(x-h)) / (pow(h,2));

 }
