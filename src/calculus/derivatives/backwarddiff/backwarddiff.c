#include "calculus/backwarddiff.h"
#include <math.h>

double (double (*f)(double), double x, double h){
    if (h == 0.0){

    return NAN;
    }

   return (f(x) - f(x-h)) / h;
}
