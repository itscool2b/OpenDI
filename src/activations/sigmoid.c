#include <math.h>
#include "../../include/activations/sigmoid.h"
#include "../../include/primitive/exponents.h"

#define opendi_e 2.7182818284590452353602874713527

double sigmoid(double x){


	return (1.0) / (1.0+(exponents(opendi_e, x*-1)));

}
