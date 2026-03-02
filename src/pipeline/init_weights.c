#include <stdlib.h>
#include <string.h>
#include "../../include/pipeline/init_weights.h"
#include "../../include/arena.h"
#include "../../include/random/random_normal.h"

double *init_weights(int n, double mean, double std){

	Arena *tmp = arena_create(n * sizeof(double) + 256);
	double *rnd = random_normal(tmp, mean, std, n);

	double *weights = malloc(n * sizeof(double));
	memcpy(weights, rnd, n * sizeof(double));

	arena_destroy(tmp);

	return weights;

}
