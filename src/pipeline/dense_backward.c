#include "../../include/pipeline/dense_backward.h"
#include "../../include/backward/activations/relu_backward.h"
#include "../../include/backward/activations/sigmoid_backward.h"
#include "../../include/backward/linalg/matmul_backward_a.h"
#include "../../include/backward/linalg/matmul_backward_b.h"

LayerGrad dense_backward(Arena *arena, double *dout, double *input, double *weights, double *cache, int m, int n, int p, ActivationType act){

	LayerGrad grad;
	int total = m * p;
	double *d_act = dout;

	if (act == ACTIVATION_RELU){

		d_act = relu_backward(arena, dout, cache, total);

	} else if (act == ACTIVATION_SIGMOID){

		d_act = sigmoid_backward(arena, dout, cache, total);

	}

	grad.d_weights = matmul_backward_b(arena, input, d_act, m, n, p);
	grad.d_input = matmul_backward_a(arena, d_act, weights, m, n, p);

	return grad;

}
