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

	fp = fopen("datasets/mnist_data/train-images.idx3-ubyte", "rb");
	fseek(fp, 16, SEEK_SET);
	raw = malloc(N_TRAIN * N_PIXELS);
	fread(raw, 1, N_TRAIN * N_PIXELS, fp);
	for (int i = 0; i < N_TRAIN * N_PIXELS; i++)
		train_img[i] = raw[i] / 255.0;
	free(raw);
	fclose(fp);

	fp = fopen("datasets/mnist_data/train-labels.idx1-ubyte", "rb");
	fseek(fp, 8, SEEK_SET);
	for (int i = 0; i < N_TRAIN; i++){

		fread(&byte, 1, 1, fp);
		train_lbl[i * N_CLASSES + byte] = 1.0;

	}
	fclose(fp);

	fp = fopen("datasets/mnist_data/t10k-images.idx3-ubyte", "rb");
	fseek(fp, 16, SEEK_SET);
	raw = malloc(N_TEST * N_PIXELS);
	fread(raw, 1, N_TEST * N_PIXELS, fp);
	for (int i = 0; i < N_TEST * N_PIXELS; i++)
		test_img[i] = raw[i] / 255.0;
	free(raw);
	fclose(fp);

	fp = fopen("datasets/mnist_data/t10k-labels.idx1-ubyte", "rb");
	fseek(fp, 8, SEEK_SET);
	for (int i = 0; i < N_TEST; i++){

		fread(&byte, 1, 1, fp);
		test_lbl[i] = byte;

	}
	fclose(fp);

	Arena *arena = arena_create(32 * 1024 * 1024);

	random_seed(42);
	double *W1 = init_weights(N_PIXELS * N_HIDDEN, 0.0, 0.05);
	double *W2 = init_weights(N_HIDDEN * N_CLASSES, 0.0, 0.1);

	printf("=== Training ===\n\n");

	for (int epoch = 0; epoch < EPOCHS; epoch++){

		double *z1_cache;
		double *h = dense_forward(arena, train_img, W1, N_TRAIN, N_PIXELS, N_HIDDEN,
		                          ACTIVATION_RELU, &z1_cache);

		double *pred = dense_forward(arena, h, W2, N_TRAIN, N_HIDDEN, N_CLASSES,
		                             ACTIVATION_SOFTMAX, NULL);

		double loss = cross_entropy(pred, train_lbl, N_TRAIN * N_CLASSES);

		if (epoch % 5 == 0){

			int *train_labels = malloc(N_TRAIN * sizeof(int));
			for (int i = 0; i < N_TRAIN; i++){
				int label = 0;
				for (int j = 0; j < N_CLASSES; j++)
					if (train_lbl[i * N_CLASSES + j] > 0.5)
						label = j;
				train_labels[i] = label;
			}

			double acc = accuracy(pred, train_labels, N_TRAIN, N_CLASSES);
			printf("Epoch %3d  loss: %.4f  acc: %.1f%%\n", epoch, loss, 100.0 * acc);
			free(train_labels);

		}

		double *d_z2 = cross_entropy_backward(arena, pred, train_lbl, N_TRAIN, N_CLASSES);

		LayerGrad grad2 = dense_backward(arena, d_z2, h, W2, NULL,
		                                 N_TRAIN, N_HIDDEN, N_CLASSES, ACTIVATION_NONE);

		LayerGrad grad1 = dense_backward(arena, grad2.d_input, train_img, W1, z1_cache,
		                                 N_TRAIN, N_PIXELS, N_HIDDEN, ACTIVATION_RELU);

		double *new_W1 = sgd_update(arena, W1, grad1.d_weights, LR, N_PIXELS * N_HIDDEN);
		double *new_W2 = sgd_update(arena, W2, grad2.d_weights, LR, N_HIDDEN * N_CLASSES);

		memcpy(W1, new_W1, N_PIXELS * N_HIDDEN * sizeof(double));
		memcpy(W2, new_W2, N_HIDDEN * N_CLASSES * sizeof(double));
		arena_clear(arena);

	}

	double *th = dense_forward(arena, test_img, W1, N_TEST, N_PIXELS, N_HIDDEN,
	                           ACTIVATION_RELU, NULL);

	double *tpred = dense_forward(arena, th, W2, N_TEST, N_HIDDEN, N_CLASSES,
	                              ACTIVATION_SOFTMAX, NULL);

	double acc = accuracy(tpred, test_lbl, N_TEST, N_CLASSES);

	printf("\n=== Predictions ===\n\n");

	for (int i = 0; i < 20; i++){

		int max_j = 0;
		for (int j = 1; j < N_CLASSES; j++)
			if (tpred[i * N_CLASSES + j] > tpred[i * N_CLASSES + max_j])
				max_j = j;

		printf("Sample %2d  pred: %d  actual: %d  %s\n",
			i + 1, max_j, test_lbl[i],
			max_j == test_lbl[i] ? "[PASS]" : "[FAIL]");

	}

	printf("\n=== Results ===\n");
	printf("Test Accuracy: %d/%d (%.1f%%)\n", (int)(acc * N_TEST), N_TEST, 100.0 * acc);

	arena_destroy(arena);
	free(train_img);
	free(train_lbl);
	free(test_img);
	free(test_lbl);
	free(W1);
	free(W2);

	return 0;

}
