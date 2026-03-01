#include "../../../include/backward/activations/softmax_backward.h"

double *softmax_backward(Arena *arena, double *dout, double *output, int n){

	double *grad = arena_push(arena, n*sizeof(double));

	double dot = 0.0;
	for (int i = 0; i < n; i++){

		dot += dout[i] * output[i];

	}

	for (int i = 0; i < n; i++){

		grad[i] = output[i] * (dout[i] - dot);

	}

	return grad;

}
