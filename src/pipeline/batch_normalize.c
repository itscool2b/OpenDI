#include "../../include/pipeline/batch_normalize.h"
#include "../../include/statistics/normalize.h"
#include <string.h>

double *batch_normalize(Arena *arena, double *features, int n_samples, int n_features){

	double *result = arena_push(arena, n_samples * n_features * sizeof(double));

	double col[n_samples];

	for (int j = 0; j < n_features; j++){

		for (int i = 0; i < n_samples; i++)
			col[i] = features[i * n_features + j];

		double *normed = normalize(arena, col, n_samples);

		for (int i = 0; i < n_samples; i++)
			result[i * n_features + j] = normed[i];

	}

	return result;

}
