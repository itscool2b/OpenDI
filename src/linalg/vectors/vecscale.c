#include <stdlib.h>
#include "linalg/vectors/vecscale.h"
#include "arena.h"
#include <stdint.h>

double *vecscale(Arena *arena, const double *arr, double scalar, size_t length){

    uint64_t usage = length * sizeof(double);
    double *resultantvec = arena_push(arena, usage);

    if(resultantvec == NULL){
        return NULL;
    }

    for (size_t i = 0; i < length; i++){
        double num = arr[i] * scalar;
        resultantvec[i] = num;
    }

    return resultantvec;

}
