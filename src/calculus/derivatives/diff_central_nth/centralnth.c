#include "calculus/centralnth.h"

double centralnth(double (*f)(double), double x, double h, int num){

	if (num == 0) return f(x);
	if (num == 1) return (f(x + h) - f(x - h)) / (2.0 * h);

	return (centralnth(f, x + h, h, num - 1) - centralnth(f, x - h, h, num - 1)) / (2.0 * h);
}
