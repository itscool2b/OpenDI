#include "calculus/centraldiff.h"

double central_difference(double (*f)(double), double x, double h)
{

if (h == 0.0){

    return 0.0;
}

return (f(x+h) - f(x-h)) / (2*h);

}
