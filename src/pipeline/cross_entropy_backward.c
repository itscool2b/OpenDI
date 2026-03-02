#include "../../include/pipeline/cross_entropy_backward.h"

double *cross_entropy_backward(Arena *arena, double *pred, double *targets, int n_samples, int n_classes){

	int n = n_samples * n_classes;
	double *grad = arena_push(arena, n * sizeof(double));

	for (int i = 0; i < n; i++){

		grad[i] = (pred[i] - targets[i]) / n_samples;

	}

	return grad;

}
