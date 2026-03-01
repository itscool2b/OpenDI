#include "../../include/loss/mse_loss.h"

double mse_loss(double *predictions, double *targets, int n){

	double sum = 0.0;

	for (int i = 0; i < n; i++){

		double diff = predictions[i] - targets[i];
		sum += diff * diff;

	}

	return sum / n;

}
