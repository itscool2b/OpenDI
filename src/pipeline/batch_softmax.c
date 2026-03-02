#include "../../include/pipeline/batch_softmax.h"
#include "../../include/primitive/exponents.h"

#define opendi_e 2.7182818284590452353602874713527

double *batch_softmax(Arena *arena, double *input, int rows, int cols){

	double *result = arena_push(arena, rows * cols * sizeof(double));

	for (int i = 0; i < rows; i++){

		double max = input[i * cols];
		for (int j = 1; j < cols; j++){

			if (input[i * cols + j] > max)
				max = input[i * cols + j];

		}

		double sum = 0.0;
		for (int j = 0; j < cols; j++){

			result[i * cols + j] = exponents(opendi_e, input[i * cols + j] - max);
			sum += result[i * cols + j];

		}

		for (int j = 0; j < cols; j++){

			result[i * cols + j] /= sum;

		}

	}

	return result;

}
