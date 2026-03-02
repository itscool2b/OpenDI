#include "../../include/pipeline/mse_backward.h"

double *mse_backward(Arena *arena, double *pred, double *targets, int n){

	double *grad = arena_push(arena, n * sizeof(double));

	for (int i = 0; i < n; i++){

		grad[i] = 2.0 * (pred[i] - targets[i]) / n;

	}

	return grad;

}
