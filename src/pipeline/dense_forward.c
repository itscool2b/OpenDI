#include "../../include/pipeline/dense_forward.h"
#include "../../include/linalg/matricies/matmul.h"
#include "../../include/activations/relu.h"
#include "../../include/activations/sigmoid.h"
#include "../../include/primitive/exponents.h"
#include <string.h>

#define opendi_e 2.7182818284590452353602874713527

double *dense_forward(Arena *arena, double *input, double *weights, int m, int n, int p, ActivationType act, double **cache){

	double *z = matmul(arena, input, weights, m, n, p);
	int total = m * p;

	if (act == ACTIVATION_NONE){

		if (cache) *cache = NULL;
		return z;

	}

	if (act == ACTIVATION_RELU){

		if (cache) *cache = z;

		double *out = arena_push(arena, total * sizeof(double));
		for (int i = 0; i < total; i++)
			out[i] = relu(z[i]);

		return out;

	}

	if (act == ACTIVATION_SIGMOID){

		double *out = arena_push(arena, total * sizeof(double));
		for (int i = 0; i < total; i++)
			out[i] = sigmoid(z[i]);

		if (cache) *cache = out;
		return out;

	}

	if (act == ACTIVATION_SOFTMAX){

		double *out = arena_push(arena, total * sizeof(double));

		for (int i = 0; i < m; i++){

			double max = z[i * p];
			for (int j = 1; j < p; j++){

				if (z[i * p + j] > max)
					max = z[i * p + j];

			}

			double sum = 0.0;
			for (int j = 0; j < p; j++){

				out[i * p + j] = exponents(opendi_e, z[i * p + j] - max);
				sum += out[i * p + j];

			}

			for (int j = 0; j < p; j++){

				out[i * p + j] /= sum;

			}

		}

		if (cache) *cache = NULL;
		return out;

	}

	if (cache) *cache = NULL;
	return z;

}
