#include <math.h>
#include "../../include/activations/softmax.h"
#include "../../include/primitive/exponents.h"

#define opendi_e 2.7182818284590452353602874713527

double *softmax(Arena *arena, double *v, int n){

	double *vector = arena_push(arena, n*sizeof(double));
	double max = v[0];
	double sum = 0;

	for (int i = 1; i < n; i++){

		if(v[i] > max){
			max = v[i];

		}
	}

	for (int i = 0; i < n; i++){

		vector[i] = exponents(opendi_e, v[i]-max);
		sum += vector[i];

	}

	for (int i = 0; i < n; i++){

		vector[i] = vector[i] / sum;

	}

	return vector;

}
