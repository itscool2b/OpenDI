#include <stdlib.h>
#include <math.h>
#include "../../include/random/random_normal.h"

#define PI 3.14159265358979323846

double *random_normal(Arena *arena, double mean, double std, int n){

	double *result = arena_push(arena, n*sizeof(double));

	for (int i = 0; i < n; i++){

		double u1 = ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
		double u2 = ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
		double z = sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2);
		result[i] = mean + std * z;

	}

	return result;

}
