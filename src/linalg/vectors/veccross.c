#include <stdlib.h>
#include "linalg/vectors/veccross.h"

double *veccross(const double *vec1, const double *vec2){

    double *r = malloc(VECCROSS_SIZE*sizeof(double));

    if (r == NULL){
        return NULL;
    }

    r[0] = (vec1[1] * vec2[2]) - (vec1[2] * vec2[1]);
    r[1] = (vec1[2] * vec2[0]) - (vec1[0] * vec2[2]);
    r[2] = (vec1[0] * vec2[1]) - (vec1[1] * vec2[0]);

    return r;
}
