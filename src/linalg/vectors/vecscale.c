#include <stdlib.h>
#include "linalg/vectors/vecscale.h"

double *vecscale(const double *arr, double scalar, size_t length){

    double *resultantvec = malloc(length * sizeof(double));

    if(resultantvec == NULL){
        return NULL;
    }

    for (size_t i = 0; i < length; i++){
        double num = arr[i] * scalar;
        resultantvec[i] = num;
    }

    return resultantvec;
}
