#include "../../include/pipeline/batch_sigmoid.h"
#include "../../include/activations/sigmoid.h"

double *batch_sigmoid(Arena *arena, double *input, int n){

	double *result = arena_push(arena, n * sizeof(double));

	for (int i = 0; i < n; i++){

		result[i] = sigmoid(input[i]);

	}

	return result;

}
