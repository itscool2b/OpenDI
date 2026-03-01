#include <math.h>
#include "../../include/statistics/normalize.h"

double *normalize(Arena *arena, double *v, int n){

	double *result = arena_push(arena, n*sizeof(double));

	double sum = 0.0;
	for (int i = 0; i < n; i++){

		sum += v[i];

	}
	double mean = sum / n;

	double var_sum = 0.0;
	for (int i = 0; i < n; i++){

		var_sum += (v[i] - mean) * (v[i] - mean);

	}
	double std = sqrt(var_sum / n);

	for (int i = 0; i < n; i++){

		result[i] = (v[i] - mean) / std;

	}

	return result;

}
