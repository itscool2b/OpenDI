#include <math.h>
#include "linalg/vectors/vecnorm.h"
#include "linalg/vectors/vecdot.h"

double vecnorm(const double *vec, size_t length){

    double magnitude = sqrt(vecdot(vec, vec, length));

    return magnitude;
}
