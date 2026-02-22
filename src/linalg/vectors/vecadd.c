#include <math.h>
#include <stdlib.h>
#include "linalg/vectors/vecadd.h"

double *vecadd(Arena *arena, const double *vec1, const double *vec2, size_t length){
    uint64_t usage = length*sizeof(double);
    double *resultantvec = arena_push(arena, usage);
    if(resultantvec == NULL){
        return NULL;
    }
    
    for(size_t i = 0; i < length; i++){
        double num = vec1[i] + vec2[i];
        resultantvec[i] = num;
    }

    return resultantvec;
}
