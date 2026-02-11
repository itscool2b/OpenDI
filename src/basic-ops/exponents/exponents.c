#include <math.h>
#include "exponents.h"

double exponents(float value, float exponent){

	if (value == 0 && exponent == 0){

	return 1.0;

	}

	return pow(value, exponent);


}

