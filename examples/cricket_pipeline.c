#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/opendi.h"

#define N_SAMPLES 20
#define N_FEATURES 8
#define EPOCHS 5000
#define LR 0.5

int main(){

	double features[N_SAMPLES * N_FEATURES];
	double targets[N_SAMPLES];

	FILE *fp = fopen("datasets/pak_vs_ind_cricket_dataset.csv", "r");
	char line[512];
	fgets(line, sizeof(line), fp);

	int row = 0;
	while (fgets(line, sizeof(line), fp) && row < N_SAMPLES){

		char *tok = strtok(line, ",");
		tok = strtok(NULL, ",");
		tok = strtok(NULL, ",");
		tok = strtok(NULL, ",");

		for (int j = 0; j < N_FEATURES; j++){

			tok = strtok(NULL, ",");
			features[row * N_FEATURES + j] = atof(tok);

		}

		tok = strtok(NULL, ",");
		targets[row] = (strncmp(tok, "Win", 3) == 0) ? 1.0 : 0.0;

		row++;

	}

	fclose(fp);

	Arena *arena = arena_create(65536);

	double *normed = batch_normalize(arena, features, N_SAMPLES, N_FEATURES);
	memcpy(features, normed, N_SAMPLES * N_FEATURES * sizeof(double));
	arena_clear(arena);

	random_seed(42);
	double *weights = init_weights(N_FEATURES, 0.0, 0.1);

	printf("=== Training ===\n\n");

	for (int epoch = 0; epoch < EPOCHS; epoch++){

		double *cache;
		double *pred = dense_forward(arena, features, weights, N_SAMPLES, N_FEATURES, 1,
		                             ACTIVATION_SIGMOID, &cache);

		double loss = mse_loss(pred, targets, N_SAMPLES);

		if (epoch % 500 == 0)
			printf("Epoch %4d  loss: %.6f\n", epoch, loss);

		double *d_loss = mse_backward(arena, pred, targets, N_SAMPLES);

		LayerGrad grad = dense_backward(arena, d_loss, features, weights, cache,
		                                N_SAMPLES, N_FEATURES, 1, ACTIVATION_SIGMOID);

		double *new_w = sgd_update(arena, weights, grad.d_weights, LR, N_FEATURES);
		memcpy(weights, new_w, N_FEATURES * sizeof(double));
		arena_clear(arena);

	}

	double *cache;
	double *pred = dense_forward(arena, features, weights, N_SAMPLES, N_FEATURES, 1,
	                             ACTIVATION_SIGMOID, &cache);

	double final_loss = mse_loss(pred, targets, N_SAMPLES);

	int labels[N_SAMPLES];
	for (int i = 0; i < N_SAMPLES; i++)
		labels[i] = (int)targets[i];

	double acc = accuracy(pred, labels, N_SAMPLES, 1);

	printf("\n=== Predictions ===\n\n");

	for (int i = 0; i < N_SAMPLES; i++){

		int p = pred[i] >= 0.5 ? 1 : 0;
		int a = (int)targets[i];

		printf("Sample %2d  pred: %.4f  class: %s  actual: %s  %s\n",
			i + 1, pred[i],
			p ? "Win " : "Lose",
			a ? "Win " : "Lose",
			p == a ? "[PASS]" : "[FAIL]");

	}

	printf("\n=== Results ===\n");
	printf("Accuracy: %d/%d (%.1f%%)\n", (int)(acc * N_SAMPLES), N_SAMPLES, 100.0 * acc);
	printf("Final loss: %.6f\n", final_loss);

	arena_destroy(arena);
	free(weights);

	return 0;

}
