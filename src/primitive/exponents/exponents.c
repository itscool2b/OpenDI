#include <math.h>
#include "../../../include/primitive/exponents.h"

double exponents(double value, double exponent){

	if (value == 0 && exponent == 0){

	return 1.0;

	}

	return pow(value, exponent);


}
