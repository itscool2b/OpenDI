#include "../../../include/backward/activations/sigmoid_backward.h"

double *sigmoid_backward(Arena *arena, double *dout, double *output, int n){

	double *grad = arena_push(arena, n*sizeof(double));

	for (int i = 0; i < n; i++){

		grad[i] = dout[i] * output[i] * (1.0 - output[i]);

	}

	return grad;

}
