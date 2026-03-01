#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/opendi.h"

#define N_TRAIN 1000
#define N_TEST 500
#define N_PIXELS 784
#define N_HIDDEN 128
#define N_CLASSES 10
#define EPOCHS 200
#define LR 1.0

int main(){

	double *train_img = malloc(N_TRAIN * N_PIXELS * sizeof(double));
	double *train_lbl = calloc(N_TRAIN * N_CLASSES, sizeof(double));
	double *test_img = malloc(N_TEST * N_PIXELS * sizeof(double));
	int *test_lbl = malloc(N_TEST * sizeof(int));

	FILE *fp;
	unsigned char *raw;
	unsigned char byte;

	fp = fopen("mnist_data/train-images.idx3-ubyte", "rb");
	fseek(fp, 16, SEEK_SET);
	raw = malloc(N_TRAIN * N_PIXELS);
	fread(raw, 1, N_TRAIN * N_PIXELS, fp);
	for (int i = 0; i < N_TRAIN * N_PIXELS; i++)
		train_img[i] = raw[i] / 255.0;
	free(raw);
	fclose(fp);

	fp = fopen("mnist_data/train-labels.idx1-ubyte", "rb");
	fseek(fp, 8, SEEK_SET);
	for (int i = 0; i < N_TRAIN; i++){

		fread(&byte, 1, 1, fp);
		train_lbl[i * N_CLASSES + byte] = 1.0;

	}
	fclose(fp);

	fp = fopen("mnist_data/t10k-images.idx3-ubyte", "rb");
	fseek(fp, 16, SEEK_SET);
	raw = malloc(N_TEST * N_PIXELS);
	fread(raw, 1, N_TEST * N_PIXELS, fp);
	for (int i = 0; i < N_TEST * N_PIXELS; i++)
		test_img[i] = raw[i] / 255.0;
	free(raw);
	fclose(fp);

	fp = fopen("mnist_data/t10k-labels.idx1-ubyte", "rb");
	fseek(fp, 8, SEEK_SET);
	for (int i = 0; i < N_TEST; i++){

		fread(&byte, 1, 1, fp);
		test_lbl[i] = byte;

	}
	fclose(fp);

	Arena *arena = arena_create(32 * 1024 * 1024);

	random_seed(42);
	double *W1_init = random_normal(arena, 0.0, 0.05, N_PIXELS * N_HIDDEN);
	double *W2_init = random_normal(arena, 0.0, 0.1, N_HIDDEN * N_CLASSES);

	double *W1 = malloc(N_PIXELS * N_HIDDEN * sizeof(double));
	double *W2 = malloc(N_HIDDEN * N_CLASSES * sizeof(double));
	memcpy(W1, W1_init, N_PIXELS * N_HIDDEN * sizeof(double));
	memcpy(W2, W2_init, N_HIDDEN * N_CLASSES * sizeof(double));
	arena_clear(arena);

	printf("=== Training ===\n\n");

	for (int epoch = 0; epoch < EPOCHS; epoch++){

		double *z1 = matmul(arena, train_img, W1, N_TRAIN, N_PIXELS, N_HIDDEN);

		double *h = arena_push(arena, N_TRAIN * N_HIDDEN * sizeof(double));
		for (int i = 0; i < N_TRAIN * N_HIDDEN; i++)
			h[i] = relu(z1[i]);

		double *z2 = matmul(arena, h, W2, N_TRAIN, N_HIDDEN, N_CLASSES);

		double *pred = softmax(arena, &z2[0], N_CLASSES);
		for (int i = 1; i < N_TRAIN; i++)
			softmax(arena, &z2[i * N_CLASSES], N_CLASSES);

		double loss = cross_entropy(pred, train_lbl, N_TRAIN * N_CLASSES);

		if (epoch % 5 == 0){

			int correct = 0;
			for (int i = 0; i < N_TRAIN; i++){

				int max_j = 0;
				for (int j = 1; j < N_CLASSES; j++)
					if (pred[i * N_CLASSES + j] > pred[i * N_CLASSES + max_j])
						max_j = j;

				int label = 0;
				for (int j = 0; j < N_CLASSES; j++)
					if (train_lbl[i * N_CLASSES + j] > 0.5)
						label = j;

				if (max_j == label) correct++;

			}

			printf("Epoch %3d  loss: %.4f  acc: %.1f%%\n",
				epoch, loss, 100.0 * correct / N_TRAIN);

		}

		double *d_z2 = arena_push(arena, N_TRAIN * N_CLASSES * sizeof(double));
		for (int i = 0; i < N_TRAIN * N_CLASSES; i++)
			d_z2[i] = (pred[i] - train_lbl[i]) / N_TRAIN;

		double *d_W2 = matmul_backward_b(arena, h, d_z2, N_TRAIN, N_HIDDEN, N_CLASSES);
		double *d_h = matmul_backward_a(arena, d_z2, W2, N_TRAIN, N_HIDDEN, N_CLASSES);
		double *d_z1 = relu_backward(arena, d_h, z1, N_TRAIN * N_HIDDEN);
		double *d_W1 = matmul_backward_b(arena, train_img, d_z1, N_TRAIN, N_PIXELS, N_HIDDEN);

		double *new_W1 = sgd_update(arena, W1, d_W1, LR, N_PIXELS * N_HIDDEN);
		double *new_W2 = sgd_update(arena, W2, d_W2, LR, N_HIDDEN * N_CLASSES);

		memcpy(W1, new_W1, N_PIXELS * N_HIDDEN * sizeof(double));
		memcpy(W2, new_W2, N_HIDDEN * N_CLASSES * sizeof(double));
		arena_clear(arena);

	}

	double *tz1 = matmul(arena, test_img, W1, N_TEST, N_PIXELS, N_HIDDEN);

	double *th = arena_push(arena, N_TEST * N_HIDDEN * sizeof(double));
	for (int i = 0; i < N_TEST * N_HIDDEN; i++)
		th[i] = relu(tz1[i]);

	double *tz2 = matmul(arena, th, W2, N_TEST, N_HIDDEN, N_CLASSES);

	double *tpred = softmax(arena, &tz2[0], N_CLASSES);
	for (int i = 1; i < N_TEST; i++)
		softmax(arena, &tz2[i * N_CLASSES], N_CLASSES);

	printf("\n=== Predictions ===\n\n");

	int correct = 0;
	for (int i = 0; i < N_TEST; i++){

		int max_j = 0;
		for (int j = 1; j < N_CLASSES; j++)
			if (tpred[i * N_CLASSES + j] > tpred[i * N_CLASSES + max_j])
				max_j = j;

		if (max_j == test_lbl[i]) correct++;

		if (i < 20)
			printf("Sample %2d  pred: %d  actual: %d  %s\n",
				i + 1, max_j, test_lbl[i],
				max_j == test_lbl[i] ? "[PASS]" : "[FAIL]");

	}

	printf("\n=== Results ===\n");
	printf("Test Accuracy: %d/%d (%.1f%%)\n", correct, N_TEST, 100.0 * correct / N_TEST);

	arena_destroy(arena);
	free(train_img);
	free(train_lbl);
	free(test_img);
	free(test_lbl);
	free(W1);
	free(W2);

	return 0;

}
