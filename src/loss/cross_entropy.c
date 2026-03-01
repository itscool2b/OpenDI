#include <math.h>
#include "../../include/loss/cross_entropy.h"

double cross_entropy(double *predictions, double *targets, int n){

	double sum = 0.0;

	for (int i = 0; i < n; i++){

		sum += targets[i] * log(predictions[i] + 1e-15);

	}

	return -sum / n;

}
