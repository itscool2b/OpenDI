#include "linalg/vectors/vecdot.h"

double vecdot(const double *vec1, const double *vec2, size_t length){

    double sum = 0;
    
    for(size_t i = 0; i < length; i++){
        sum += vec1[i] * vec2[i];
    }

    return sum;
}
