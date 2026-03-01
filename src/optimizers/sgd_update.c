#include "../../include/optimizers/sgd_update.h"

double *sgd_update(Arena *arena, double *weights, double *grads, double lr, int n){

	double *result = arena_push(arena, n*sizeof(double));

	for (int i = 0; i < n; i++){

		result[i] = weights[i] - lr * grads[i];

	}

	return result;

}
