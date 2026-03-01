#include <stdlib.h>
#include "../../include/random/random_uniform.h"

double *random_uniform(Arena *arena, double min, double max, int n){

	double *result = arena_push(arena, n*sizeof(double));

	for (int i = 0; i < n; i++){

		result[i] = min + (max - min) * ((double)rand() / RAND_MAX);

	}

	return result;

}
