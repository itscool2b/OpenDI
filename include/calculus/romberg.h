#ifndef ROMBERG_H
#define ROMBERG_H

double romberg_integrate(double (*f)(double), double a, double b, double eps, int k_max);

#endif
