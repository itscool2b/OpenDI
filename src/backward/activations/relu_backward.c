#include "../../../include/backward/activations/relu_backward.h"

double *relu_backward(Arena *arena, double *dout, double *input, int n){

	double *grad = arena_push(arena, n*sizeof(double));

	for (int i = 0; i < n; i++){

		grad[i] = (input[i] > 0) ? dout[i] : 0.0;

	}

	return grad;

}
