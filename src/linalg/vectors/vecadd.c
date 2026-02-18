#include <math.h>
#include <stdlib.h>
#include "linalg/vectors/vecadd.h"

double *vecadd(const double *vec1, const double *vec2, size_t length){

    double *resultantvec = malloc(length*sizeof(double));
    if(resultantvec == NULL){
        return NULL;
    }
    
    for(size_t i = 0; i < length; i++){
        double num = vec1[i] + vec2[i];
        resultantvec[i] = num;
    }

    return resultantvec;
}
