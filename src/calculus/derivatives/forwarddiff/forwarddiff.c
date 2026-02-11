#include "forwarddiff.h"


double forwarddiff(double (*f)(double), double x, double h){

    if (h == 0.0){
    return 0.0;
    }

    return (f(x+h)-f(x)) / (h);
}
