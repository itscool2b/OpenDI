#include "../../include/pipeline/accuracy.h"

double accuracy(double *pred, int *labels, int n_samples, int n_classes){

	int correct = 0;

	if (n_classes == 1){

		for (int i = 0; i < n_samples; i++){

			int p = pred[i] >= 0.5 ? 1 : 0;
			if (p == labels[i]) correct++;

		}

	} else {

		for (int i = 0; i < n_samples; i++){

			int max_j = 0;
			for (int j = 1; j < n_classes; j++){

				if (pred[i * n_classes + j] > pred[i * n_classes + max_j])
					max_j = j;

			}

			if (max_j == labels[i]) correct++;

		}

	}

	return (double)correct / n_samples;

}
