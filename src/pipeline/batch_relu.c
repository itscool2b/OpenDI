#include "../../include/pipeline/batch_relu.h"
#include "../../include/activations/relu.h"

double *batch_relu(Arena *arena, double *input, int n){

	double *result = arena_push(arena, n * sizeof(double));

	for (int i = 0; i < n; i++){

		result[i] = relu(input[i]);

	}

	return result;

}
