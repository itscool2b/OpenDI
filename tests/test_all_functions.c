/*
 * Comprehensive test for EVERY function in the OpenDI C library.
 * Compile:
 *   gcc -Iinclude tests/test_all_functions.c \
 *     src/primitive/add/add.c src/primitive/subtract/subtract.c \
 *     src/primitive/multiply/multiply.c src/primitive/divide/divide.c \
 *     src/primitive/absolute/absolute.c src/primitive/minmax/minmax.c \
 *     src/primitive/rounding/rounding.c src/primitive/exponents/exponents.c \
 *     src/calculus/derivatives/forwarddiff/forwarddiff.c \
 *     src/calculus/derivatives/backwarddiff/backwarddiff.c \
 *     src/calculus/derivatives/centraldiff/centraldiff.c \
 *     src/calculus/derivatives/secondderivative/secondderivative.c \
 *     src/calculus/derivatives/diff_central_nth/centralnth.c \
 *     src/calculus/integrals/romberg/romberg.c \
 *     src/linalg/vectors/vecadd.c src/linalg/vectors/vecscale.c \
 *     src/linalg/vectors/vecdot.c src/linalg/vectors/veccross.c \
 *     src/linalg/vectors/vecnorm.c \
 *     src/linalg/matricies/matmul.c src/linalg/matricies/matadd.c \
 *     src/linalg/matricies/matscale.c src/linalg/matricies/mattranspose.c \
 *     src/activations/relu.c src/activations/sigmoid.c src/activations/softmax.c \
 *     src/loss/mse_loss.c src/loss/cross_entropy.c \
 *     src/backward/activations/relu_backward.c \
 *     src/backward/activations/sigmoid_backward.c \
 *     src/backward/activations/softmax_backward.c \
 *     src/backward/linalg/matmul_backward_a.c \
 *     src/backward/linalg/matmul_backward_b.c \
 *     src/optimizers/sgd_update.c \
 *     src/random/random_seed.c src/random/random_uniform.c \
 *     src/random/random_normal.c \
 *     src/statistics/normalize.c \
 *     src/pipeline/batch_relu.c src/pipeline/batch_sigmoid.c \
 *     src/pipeline/batch_softmax.c src/pipeline/batch_normalize.c \
 *     src/pipeline/mse_backward.c src/pipeline/cross_entropy_backward.c \
 *     src/pipeline/accuracy.c src/pipeline/init_weights.c \
 *     src/pipeline/dense_forward.c src/pipeline/dense_backward.c \
 *     -o test_bin/test_all_functions -lm
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "arena.h"
#include "primitive/add.h"
#include "primitive/subtract.h"
#include "primitive/multiply.h"
#include "primitive/divide.h"
#include "primitive/absolute.h"
#include "primitive/minmax.h"
#include "primitive/rounding.h"
#include "primitive/exponents.h"
#include "calculus/forwarddiff.h"
#include "calculus/backwarddiff.h"
#include "calculus/centraldiff.h"
#include "calculus/secondderivative.h"
#include "calculus/centralnth.h"
#include "calculus/romberg.h"
#include "linalg/vectors/vecadd.h"
#include "linalg/vectors/vecscale.h"
#include "linalg/vectors/vecdot.h"
#include "linalg/vectors/veccross.h"
#include "linalg/vectors/vecnorm.h"
#include "linalg/matricies/matmul.h"
#include "linalg/matricies/matadd.h"
#include "linalg/matricies/matscale.h"
#include "linalg/matricies/mattranspose.h"
#include "activations/relu.h"
#include "activations/sigmoid.h"
#include "activations/softmax.h"
#include "loss/mse_loss.h"
#include "loss/cross_entropy.h"
#include "backward/activations/relu_backward.h"
#include "backward/activations/sigmoid_backward.h"
#include "backward/activations/softmax_backward.h"
#include "backward/linalg/matmul_backward_a.h"
#include "backward/linalg/matmul_backward_b.h"
#include "optimizers/sgd_update.h"
#include "random/random_seed.h"
#include "random/random_uniform.h"
#include "random/random_normal.h"
#include "statistics/normalize.h"
#include "pipeline/batch_relu.h"
#include "pipeline/batch_sigmoid.h"
#include "pipeline/batch_softmax.h"
#include "pipeline/batch_normalize.h"
#include "pipeline/mse_backward.h"
#include "pipeline/cross_entropy_backward.h"
#include "pipeline/accuracy.h"
#include "pipeline/init_weights.h"
#include "pipeline/dense_forward.h"
#include "pipeline/dense_backward.h"

#define EPSILON 1e-6

int test_passed = 0;
int test_failed = 0;

void check(int condition, const char *test_name)
{
	if (condition) {
		test_passed++;
	} else {
		printf("[FAIL] %s\n", test_name);
		test_failed++;
	}
}

void check_val(const char *name, double got, double expected, double eps)
{
	if (fabs(got - expected) < eps) {
		test_passed++;
	} else {
		printf("[FAIL] %s — got %f, expected %f\n", name, got, expected);
		test_failed++;
	}
}

void check_arr(const char *name, double *got, double *expected, int n, double eps)
{
	for (int i = 0; i < n; i++) {
		if (fabs(got[i] - expected[i]) > eps) {
			printf("[FAIL] %s — index %d: got %f, expected %f\n", name, i, got[i], expected[i]);
			test_failed++;
			return;
		}
	}
	test_passed++;
}

double square(double x) { return x * x; }
double cube(double x) { return x * x * x; }
double identity(double x) { return x; }
double constant(double x) { (void)x; return 5.0; }

int main()
{
	Arena *arena = arena_create(1024 * 1024);

	/* ========== PRIMITIVES ========== */
	printf("=== Primitives ===\n");

	check_val("add(1,2,3)", add_numbers(3, 1.0, 2.0, 3.0), 6.0, EPSILON);
	check_val("add(10,20)", add_numbers(2, 10.0, 20.0), 30.0, EPSILON);
	check_val("add(single)", add_numbers(1, 42.0), 42.0, EPSILON);
	check_val("add(negative)", add_numbers(3, -1.0, -2.0, -3.0), -6.0, EPSILON);

	check_val("subtract(10,3)", subtract_numbers(2, 10.0, 3.0), 7.0, EPSILON);
	check_val("subtract(100,20,5)", subtract_numbers(3, 100.0, 20.0, 5.0), 75.0, EPSILON);
	check_val("subtract(neg)", subtract_numbers(2, 5.0, -3.0), 8.0, EPSILON);

	check_val("multiply(2,3,4)", multiply_numbers(3, 2.0, 3.0, 4.0), 24.0, EPSILON);
	check_val("multiply(5,10)", multiply_numbers(2, 5.0, 10.0), 50.0, EPSILON);
	check_val("multiply(zero)", multiply_numbers(3, 1.0, 0.0, 5.0), 0.0, EPSILON);

	check_val("divide(100,5,2)", divide_numbers(3, 100.0, 5.0, 2.0), 10.0, EPSILON);
	check_val("divide(50,10)", divide_numbers(2, 50.0, 10.0), 5.0, EPSILON);

	check_val("absolute(-5)", absolute(-5.0), 5.0, EPSILON);
	check_val("absolute(3)", absolute(3.0), 3.0, EPSILON);
	check_val("absolute(0)", absolute(0.0), 0.0, EPSILON);

	/* minmax: decision=0 for min, decision=1 for max */
	check_val("min(3,1,2)", minmax(0, 3, 3.0, 1.0, 2.0), 1.0, EPSILON);
	check_val("max(3,1,2)", minmax(1, 3, 3.0, 1.0, 2.0), 3.0, EPSILON);
	check_val("min(neg)", minmax(0, 2, -5.0, -3.0), -5.0, EPSILON);
	check_val("max(neg)", minmax(1, 2, -5.0, -3.0), -3.0, EPSILON);

	check_val("round floor 3.7", roundval("floor", 3.7), 3.0, EPSILON);
	check_val("round ceil 3.2", roundval("ceil", 3.2), 4.0, EPSILON);
	check_val("round round 3.5", roundval("round", 3.5), 3.5, EPSILON);
	check_val("round floor neg", roundval("floor", -2.3), -3.0, EPSILON);

	check_val("exponents(2,10)", exponents(2.0, 10.0), 1024.0, EPSILON);
	check_val("exponents(3,3)", exponents(3.0, 3.0), 27.0, EPSILON);
	check_val("exponents(25,0.5)", exponents(25.0, 0.5), 5.0, EPSILON);
	check_val("exponents(x,0)", exponents(7.0, 0.0), 1.0, EPSILON);

	/* ========== CALCULUS ========== */
	printf("=== Calculus ===\n");

	check_val("forwarddiff x^2 at 3", forwarddiff(square, 3.0, 0.0001), 6.0, 0.01);
	check_val("forwarddiff x^3 at 2", forwarddiff(cube, 2.0, 0.0001), 12.0, 0.01);
	check_val("forwarddiff const", forwarddiff(constant, 5.0, 0.0001), 0.0, 0.01);

	check_val("backwarddiff x^2 at 3", backwarddiff(square, 3.0, 0.0001), 6.0, 0.01);
	check_val("backwarddiff x^3 at 2", backwarddiff(cube, 2.0, 0.0001), 12.0, 0.01);

	check_val("central_diff x^2 at 3", central_difference(square, 3.0, 0.0001), 6.0, 1e-4);
	check_val("central_diff x^3 at 2", central_difference(cube, 2.0, 0.0001), 12.0, 1e-4);

	check_val("secondderiv x^2", secondderivative(square, 3.0, 0.001), 2.0, 0.1);
	check_val("secondderiv x^3 at 2", secondderivative(cube, 2.0, 0.001), 12.0, 0.1);

	check_val("centralnth x^2 n=1", centralnth(square, 3.0, 0.001, 1), 6.0, 0.01);
	check_val("centralnth x^2 n=2", centralnth(square, 3.0, 0.001, 2), 2.0, 0.1);
	check_val("centralnth x^2 n=0", centralnth(square, 3.0, 0.001, 0), 9.0, EPSILON);

	check_val("romberg x^2 [0,1]", romberg_integrate(square, 0.0, 1.0, 1e-8, 10), 1.0/3.0, 1e-5);
	check_val("romberg x [0,1]", romberg_integrate(identity, 0.0, 1.0, 1e-8, 10), 0.5, 1e-5);
	check_val("romberg const [0,2]", romberg_integrate(constant, 0.0, 2.0, 1e-8, 10), 10.0, 1e-5);

	/* ========== VECTORS ========== */
	printf("=== Vectors ===\n");

	{
		double a[] = {1, 2, 3};
		double b[] = {4, 5, 6};
		double exp_add[] = {5, 7, 9};
		double *r = vecadd(arena, a, b, 3);
		check_arr("vecadd", r, exp_add, 3, EPSILON);
	}

	{
		double a[] = {1, 2, 3};
		double exp_scale[] = {2, 4, 6};
		double *r = vecscale(arena, a, 2.0, 3);
		check_arr("vecscale", r, exp_scale, 3, EPSILON);
	}

	{
		double a[] = {1, 2, 3};
		double b[] = {4, 5, 6};
		check_val("vecdot", vecdot(a, b, 3), 32.0, EPSILON);
	}

	{
		double a[] = {1, 0, 0};
		double b[] = {0, 1, 0};
		double exp_cross[] = {0, 0, 1};
		double *r = veccross(arena, a, b);
		check_arr("veccross", r, exp_cross, 3, EPSILON);
	}

	{
		double a[] = {0, 1, 0};
		double b[] = {0, 0, 1};
		double exp_cross[] = {1, 0, 0};
		double *r = veccross(arena, a, b);
		check_arr("veccross j x k", r, exp_cross, 3, EPSILON);
	}

	{
		double a[] = {3, 4};
		check_val("vecnorm 3,4", vecnorm(a, 2), 5.0, EPSILON);
	}
	{
		double a[] = {1, 0, 0};
		check_val("vecnorm unit", vecnorm(a, 3), 1.0, EPSILON);
	}

	/* ========== MATRICES ========== */
	printf("=== Matrices ===\n");

	{
		double a[] = {1, 2, 3, 4};
		double b[] = {5, 6, 7, 8};
		double exp[] = {19, 22, 43, 50};
		double *r = matmul(arena, a, b, 2, 2, 2);
		check_arr("matmul 2x2", r, exp, 4, EPSILON);
	}

	{
		double a[] = {1, 2, 3};
		double b[] = {4, 5, 6};
		double exp[] = {32};
		double *r = matmul(arena, a, b, 1, 3, 1);
		check_arr("matmul 1x3 x 3x1", r, exp, 1, EPSILON);
	}

	{
		double a[] = {1, 2, 3, 4};
		double b[] = {10, 20, 30, 40};
		double exp[] = {11, 22, 33, 44};
		double *r = matadd(arena, a, b, 2, 2);
		check_arr("matadd", r, exp, 4, EPSILON);
	}

	{
		double a[] = {1, 2, 3, 4};
		double exp[] = {3, 6, 9, 12};
		double *r = matscale(arena, a, 3.0, 2, 2);
		check_arr("matscale", r, exp, 4, EPSILON);
	}

	{
		double a[] = {1, 2, 3, 4, 5, 6};
		double exp[] = {1, 4, 2, 5, 3, 6};
		double *r = mattranspose(arena, a, 2, 3);
		check_arr("mattranspose", r, exp, 6, EPSILON);
	}

	{
		double a[] = {1, 2, 3, 4};
		double *t = mattranspose(arena, a, 2, 2);
		double exp[] = {1, 3, 2, 4};
		check_arr("mattranspose 2x2", t, exp, 4, EPSILON);
	}

	/* ========== ACTIVATIONS ========== */
	printf("=== Activations ===\n");

	check_val("relu(5)", relu(5.0), 5.0, EPSILON);
	check_val("relu(-5)", relu(-5.0), 0.0, EPSILON);
	check_val("relu(0)", relu(0.0), 0.0, EPSILON);
	check_val("relu(0.001)", relu(0.001), 0.001, EPSILON);

	check_val("sigmoid(0)", sigmoid(0.0), 0.5, EPSILON);
	check_val("sigmoid(large)", sigmoid(100.0), 1.0, 0.001);
	check_val("sigmoid(neg large)", sigmoid(-100.0), 0.0, 0.001);

	{
		double v[] = {1, 2, 3};
		double *r = softmax(arena, v, 3);
		double sum = r[0] + r[1] + r[2];
		check_val("softmax sum", sum, 1.0, 1e-5);
		check(r[2] > r[1] && r[1] > r[0], "softmax order");
	}

	{
		double v[] = {1, 1, 1};
		double *r = softmax(arena, v, 3);
		check_val("softmax uniform", r[0], 1.0/3.0, 1e-5);
		check_val("softmax uniform 2", r[1], 1.0/3.0, 1e-5);
	}

	/* ========== LOSS ========== */
	printf("=== Loss ===\n");

	{
		double p[] = {1, 2, 3};
		double t[] = {1, 2, 3};
		check_val("mse_loss perfect", mse_loss(p, t, 3), 0.0, EPSILON);
	}

	{
		double p[] = {1, 0};
		double t[] = {0, 1};
		check_val("mse_loss", mse_loss(p, t, 2), 1.0, EPSILON);
	}

	{
		double p[] = {0.9, 0.1};
		double t[] = {1.0, 0.0};
		double ce = cross_entropy(p, t, 2);
		check(ce > 0, "cross_entropy positive");
	}

	/* ========== BACKWARD ========== */
	printf("=== Backward ===\n");

	{
		double dout[] = {1, 1, 1};
		double input[] = {5, -3, 0.1};
		double exp[] = {1, 0, 1};
		double *r = relu_backward(arena, dout, input, 3);
		check_arr("relu_backward", r, exp, 3, EPSILON);
	}

	{
		double dout[] = {1, 1, 1};
		double input[] = {-1, -2, -0.5};
		double exp[] = {0, 0, 0};
		double *r = relu_backward(arena, dout, input, 3);
		check_arr("relu_backward all neg", r, exp, 3, EPSILON);
	}

	{
		double dout[] = {1, 1};
		double output[] = {0.5, 0.5};
		double exp[] = {0.25, 0.25};
		double *r = sigmoid_backward(arena, dout, output, 2);
		check_arr("sigmoid_backward", r, exp, 2, EPSILON);
	}

	{
		double dout[] = {1, 0, 0};
		double v[] = {1, 2, 3};
		double *sm = softmax(arena, v, 3);
		double *r = softmax_backward(arena, dout, sm, 3);
		check(r != NULL, "softmax_backward non-null");
	}

	{
		/* matmul_backward_a: dA = dout @ B^T */
		double dout[] = {1, 0, 0, 1};  /* 2x2 */
		double b[] = {1, 0, 0, 1};     /* 2x2 */
		double *r = matmul_backward_a(arena, dout, b, 2, 2, 2);
		double exp[] = {1, 0, 0, 1};
		check_arr("matmul_backward_a identity", r, exp, 4, EPSILON);
	}

	{
		/* matmul_backward_b: dB = A^T @ dout */
		double a[] = {1, 0, 0, 1};     /* 2x2 */
		double dout[] = {1, 0, 0, 1};  /* 2x2 */
		double *r = matmul_backward_b(arena, a, dout, 2, 2, 2);
		double exp[] = {1, 0, 0, 1};
		check_arr("matmul_backward_b identity", r, exp, 4, EPSILON);
	}

	/* ========== OPTIMIZER ========== */
	printf("=== Optimizer ===\n");

	{
		double w[] = {1, 2, 3};
		double g[] = {0.1, 0.2, 0.3};
		double exp[] = {0.9, 1.8, 2.7};
		double *r = sgd_update(arena, w, g, 1.0, 3);
		check_arr("sgd_update", r, exp, 3, EPSILON);
	}

	{
		double w[] = {1, 2, 3};
		double g[] = {1, 1, 1};
		double exp[] = {0.9, 1.9, 2.9};
		double *r = sgd_update(arena, w, g, 0.1, 3);
		check_arr("sgd_update lr=0.1", r, exp, 3, EPSILON);
	}

	/* ========== RANDOM ========== */
	printf("=== Random ===\n");

	random_seed(42);
	{
		double *u = random_uniform(arena, 0.0, 1.0, 10);
		int in_range = 1;
		for (int i = 0; i < 10; i++) {
			if (u[i] < 0.0 || u[i] > 1.0) in_range = 0;
		}
		check(in_range, "random_uniform range");
	}

	random_seed(42);
	{
		double *a = random_uniform(arena, 0.0, 1.0, 5);
		double first_a = a[0];
		random_seed(42);
		double *b = random_uniform(arena, 0.0, 1.0, 5);
		check_val("random_seed deterministic", b[0], first_a, EPSILON);
	}

	{
		double *n = random_normal(arena, 0.0, 1.0, 100);
		double sum = 0;
		for (int i = 0; i < 100; i++) sum += n[i];
		double mean = sum / 100.0;
		check(fabs(mean) < 1.0, "random_normal mean near 0");
	}

	/* ========== STATISTICS ========== */
	printf("=== Statistics ===\n");

	{
		double v[] = {2, 4, 4, 4, 5, 5, 7, 9};
		double *r = normalize(arena, v, 8);
		double sum = 0;
		for (int i = 0; i < 8; i++) sum += r[i];
		check_val("normalize mean ~0", sum / 8.0, 0.0, 1e-5);
	}

	/* ========== PIPELINE ========== */
	printf("=== Pipeline ===\n");

	{
		double v[] = {-1, 2, -3, 4};
		double exp[] = {0, 2, 0, 4};
		double *r = batch_relu(arena, v, 4);
		check_arr("batch_relu", r, exp, 4, EPSILON);
	}

	{
		double v[] = {0, 0, 0};
		double exp[] = {0.5, 0.5, 0.5};
		double *r = batch_sigmoid(arena, v, 3);
		check_arr("batch_sigmoid", r, exp, 3, EPSILON);
	}

	{
		double v[] = {1, 2, 3, 1, 1, 1};
		double *r = batch_softmax(arena, v, 2, 3);
		double sum0 = r[0] + r[1] + r[2];
		double sum1 = r[3] + r[4] + r[5];
		check_val("batch_softmax row0 sum", sum0, 1.0, 1e-5);
		check_val("batch_softmax row1 sum", sum1, 1.0, 1e-5);
	}

	{
		double v[] = {1, 10, 3, 30, 5, 50};
		double *r = batch_normalize(arena, v, 3, 2);
		check(r != NULL, "batch_normalize non-null");
		/* column 0: [1,3,5] should be normalized */
		/* column 1: [10,30,50] should be normalized */
	}

	{
		double p[] = {1, 0};
		double t[] = {0, 1};
		double *r = mse_backward(arena, p, t, 2);
		check(r != NULL, "mse_backward non-null");
		check(r[0] > 0 && r[1] < 0, "mse_backward sign");
	}

	{
		double p[] = {0.9, 0.1, 0.1, 0.9};
		double t[] = {1, 0, 0, 1};
		double *r = cross_entropy_backward(arena, p, t, 2, 2);
		check(r != NULL, "cross_entropy_backward non-null");
	}

	{
		double p[] = {0.9, 0.1, 0.2, 0.8};
		int labels[] = {0, 1};
		double acc = accuracy(p, labels, 2, 2);
		check_val("accuracy perfect", acc, 1.0, EPSILON);
	}

	{
		double p[] = {0.1, 0.9, 0.2, 0.8};
		int labels[] = {0, 0};
		double acc = accuracy(p, labels, 2, 2);
		check_val("accuracy zero", acc, 0.0, EPSILON);
	}

	random_seed(42);
	{
		double *w = init_weights(10, 0.0, 0.1);
		check(w != NULL, "init_weights non-null");
		int ok = 1;
		for (int i = 0; i < 10; i++) {
			if (fabs(w[i]) > 10.0) ok = 0;
		}
		check(ok, "init_weights reasonable values");
		free(w);
	}

	/* ========== DENSE FORWARD + BACKWARD (full pipeline) ========== */
	printf("=== Dense Forward/Backward ===\n");

	arena_clear(arena);

	{
		/* Simple 2x2 input, 2x1 weights, sigmoid */
		double input[] = {1.0, 2.0, 3.0, 4.0};
		double weights[] = {0.1, 0.2};
		double *cache = NULL;

		double *pred = dense_forward(arena, input, weights, 2, 2, 1, ACTIVATION_SIGMOID, &cache);
		check(pred != NULL, "dense_forward sigmoid non-null");
		check(cache != NULL, "dense_forward sigmoid cache non-null");
		check(pred[0] > 0 && pred[0] < 1, "dense_forward sigmoid range");
		check(pred[1] > 0 && pred[1] < 1, "dense_forward sigmoid range 2");
	}

	arena_clear(arena);

	{
		/* ReLU activation */
		double input[] = {-1.0, 2.0, 3.0, -4.0};
		double weights[] = {1.0, 1.0};
		double *cache = NULL;

		double *pred = dense_forward(arena, input, weights, 2, 2, 1, ACTIVATION_RELU, &cache);
		check(pred != NULL, "dense_forward relu non-null");
		check(cache != NULL, "dense_forward relu cache");
		check(pred[0] >= 0 && pred[1] >= 0, "dense_forward relu >= 0");
	}

	arena_clear(arena);

	{
		/* No activation */
		double input[] = {1.0, 2.0, 3.0, 4.0};
		double weights[] = {1.0, 0.0, 0.0, 1.0};
		double *cache = NULL;

		double *pred = dense_forward(arena, input, weights, 2, 2, 2, ACTIVATION_NONE, &cache);
		check(pred != NULL, "dense_forward none non-null");
		double exp[] = {1, 2, 3, 4};
		check_arr("dense_forward identity", pred, exp, 4, EPSILON);
	}

	arena_clear(arena);

	{
		/* Softmax activation */
		double input[] = {1.0, 2.0, 3.0, 4.0};
		double weights[] = {1.0, 0.0, 0.0, 1.0};
		double *cache = NULL;

		double *pred = dense_forward(arena, input, weights, 2, 2, 2, ACTIVATION_SOFTMAX, &cache);
		check(pred != NULL, "dense_forward softmax non-null");
		double sum0 = pred[0] + pred[1];
		double sum1 = pred[2] + pred[3];
		check_val("dense_forward softmax row0", sum0, 1.0, 1e-5);
		check_val("dense_forward softmax row1", sum1, 1.0, 1e-5);
	}

	arena_clear(arena);

	{
		/* Full forward-backward pass */
		double input[] = {0.5, 0.3};         /* 1x2 */
		random_seed(42);
		double *weights = init_weights(2, 0.0, 0.1);  /* 2x1 */
		double *cache = NULL;

		double *pred = dense_forward(arena, input, weights, 1, 2, 1, ACTIVATION_SIGMOID, &cache);
		double target[] = {1.0};
		double loss = mse_loss(pred, target, 1);
		check(loss >= 0.0, "dense pipeline loss >= 0");

		double *dloss = mse_backward(arena, pred, target, 1);
		LayerGrad grad = dense_backward(arena, dloss, input, weights, cache, 1, 2, 1, ACTIVATION_SIGMOID);
		check(grad.d_weights != NULL, "dense_backward d_weights non-null");
		check(grad.d_input != NULL, "dense_backward d_input non-null");

		double *new_w = sgd_update(arena, weights, grad.d_weights, 0.5, 2);
		check(new_w != NULL, "sgd_update result non-null");

		free(weights);
	}

	/* ========== TRAINING LOOP ========== */
	printf("=== Training Loop ===\n");

	arena_clear(arena);

	{
		int n_samples = 4;
		int n_features = 1;
		double features[] = {0.1, 0.3, 0.7, 0.9};
		double targets[] = {0.0, 0.0, 1.0, 1.0};

		random_seed(42);
		double *weights = init_weights(n_features, 0.0, 0.1);

		double last_loss = 1e9;
		for (int epoch = 0; epoch < 1000; epoch++) {
			double *cache = NULL;
			double *pred = dense_forward(arena, features, weights, n_samples, n_features, 1, ACTIVATION_SIGMOID, &cache);
			last_loss = mse_loss(pred, targets, n_samples);

			double *dloss = mse_backward(arena, pred, targets, n_samples);
			LayerGrad grad = dense_backward(arena, dloss, features, weights, cache, n_samples, n_features, 1, ACTIVATION_SIGMOID);

			double *new_w = sgd_update(arena, weights, grad.d_weights, 1.0, n_features);
			for (int i = 0; i < n_features; i++) weights[i] = new_w[i];

			arena_clear(arena);
		}

		check(last_loss < 0.3, "training loss < 0.3");
		free(weights);
	}

	/* ========== ARENA ========== */
	printf("=== Arena ===\n");

	{
		Arena *a = arena_create(4096);
		check(a != NULL, "arena_create");
		u64 base = sizeof(Arena);

		void *p = arena_push(a, 64);
		check(p != NULL, "arena_push");
		check(a->position == base + 64, "arena position");

		arena_clear(a);
		check(a->position == base, "arena_clear");

		void *p2 = arena_push(a, 128);
		check(p2 != NULL, "arena_push after clear");

		arena_pop(a, 64);
		check(a->position == base + 64, "arena_pop");

		arena_pop_to(a, base);
		check(a->position == base, "arena_pop_to");

		arena_destroy(a);
	}

	arena_destroy(arena);

	printf("\n=== Results: %d passed, %d failed ===\n", test_passed, test_failed);
	return test_failed > 0 ? 1 : 0;
}
