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

	FILE *fp = fopen("pak_vs_ind_cricket_dataset.csv", "r");
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

	double col[N_SAMPLES];
	for (int j = 0; j < N_FEATURES; j++){

		for (int i = 0; i < N_SAMPLES; i++)
			col[i] = features[i * N_FEATURES + j];

		double *normed = normalize(arena, col, N_SAMPLES);

		for (int i = 0; i < N_SAMPLES; i++)
			features[i * N_FEATURES + j] = normed[i];

		arena_clear(arena);

	}

	random_seed(42);
	double *init = random_normal(arena, 0.0, 0.1, N_FEATURES);
	double weights[N_FEATURES];
	memcpy(weights, init, N_FEATURES * sizeof(double));
	arena_clear(arena);

	printf("=== Training ===\n\n");

	for (int epoch = 0; epoch < EPOCHS; epoch++){

		double *z = matmul(arena, features, weights, N_SAMPLES, N_FEATURES, 1);

		double pred[N_SAMPLES];
		for (int i = 0; i < N_SAMPLES; i++)
			pred[i] = sigmoid(z[i]);

		double loss = mse_loss(pred, targets, N_SAMPLES);

		if (epoch % 500 == 0)
			printf("Epoch %4d  loss: %.6f\n", epoch, loss);

		double d_loss[N_SAMPLES];
		for (int i = 0; i < N_SAMPLES; i++)
			d_loss[i] = 2.0 * (pred[i] - targets[i]) / N_SAMPLES;

		double *d_sig = sigmoid_backward(arena, d_loss, pred, N_SAMPLES);
		double *d_w = matmul_backward_b(arena, features, d_sig, N_SAMPLES, N_FEATURES, 1);
		double *new_w = sgd_update(arena, weights, d_w, LR, N_FEATURES);

		memcpy(weights, new_w, N_FEATURES * sizeof(double));
		arena_clear(arena);

	}

	double *z = matmul(arena, features, weights, N_SAMPLES, N_FEATURES, 1);

	double pred[N_SAMPLES];
	for (int i = 0; i < N_SAMPLES; i++)
		pred[i] = sigmoid(z[i]);

	double final_loss = mse_loss(pred, targets, N_SAMPLES);

	printf("\n=== Predictions ===\n\n");

	int correct = 0;
	for (int i = 0; i < N_SAMPLES; i++){

		int p = pred[i] >= 0.5 ? 1 : 0;
		int a = (int)targets[i];
		if (p == a) correct++;

		printf("Sample %2d  pred: %.4f  class: %s  actual: %s  %s\n",
			i + 1, pred[i],
			p ? "Win " : "Lose",
			a ? "Win " : "Lose",
			p == a ? "[PASS]" : "[FAIL]");

	}

	printf("\n=== Results ===\n");
	printf("Accuracy: %d/%d (%.1f%%)\n", correct, N_SAMPLES, 100.0 * correct / N_SAMPLES);
	printf("Final loss: %.6f\n", final_loss);

	arena_destroy(arena);

	return 0;

}
