#include "../../include/arena.h"
#include "../../include/primitive/add.h"
#include "../../include/primitive/subtract.h"
#include "../../include/primitive/multiply.h"
#include "../../include/primitive/divide.h"
#include "../../include/primitive/minmax.h"
#include "../../include/primitive/absolute.h"
#include "../../include/primitive/rounding.h"
#include "../../include/primitive/exponents.h"
#include "../../include/activations/relu.h"
#include "../../include/activations/sigmoid.h"
#include "../../include/activations/softmax.h"
#include "../../include/calculus/forwarddiff.h"
#include "../../include/calculus/backwarddiff.h"
#include "../../include/calculus/centraldiff.h"
#include "../../include/calculus/secondderivative.h"
#include "../../include/calculus/centralnth.h"
#include "../../include/calculus/romberg.h"
#include "../../include/linalg/vectors/vecadd.h"
#include "../../include/linalg/vectors/vecscale.h"
#include "../../include/linalg/vectors/veccross.h"
#include "../../include/linalg/vectors/vecdot.h"
#include "../../include/linalg/vectors/vecnorm.h"
#include "../../include/linalg/matricies/matmul.h"
#include "../../include/linalg/matricies/matadd.h"
#include "../../include/linalg/matricies/matscale.h"
#include "../../include/linalg/matricies/mattranspose.h"
#include "../../include/loss/mse_loss.h"
#include "../../include/loss/cross_entropy.h"
#include "../../include/backward/activations/relu_backward.h"
#include "../../include/backward/activations/sigmoid_backward.h"
#include "../../include/backward/activations/softmax_backward.h"
#include "../../include/backward/linalg/matmul_backward_a.h"
#include "../../include/backward/linalg/matmul_backward_b.h"
#include "../../include/optimizers/sgd_update.h"
#include "../../include/random/random_seed.h"
#include "../../include/random/random_uniform.h"
#include "../../include/random/random_normal.h"
#include "../../include/statistics/normalize.h"
#include "../../include/pipeline/pipeline_types.h"
#include "../../include/pipeline/batch_relu.h"
#include "../../include/pipeline/batch_sigmoid.h"
#include "../../include/pipeline/batch_softmax.h"
#include "../../include/pipeline/batch_normalize.h"
#include "../../include/pipeline/mse_backward.h"
#include "../../include/pipeline/cross_entropy_backward.h"
#include "../../include/pipeline/accuracy.h"
#include "../../include/pipeline/init_weights.h"
#include "../../include/pipeline/dense_forward.h"
#include "../../include/pipeline/dense_backward.h"

#include <stdlib.h>
#include <string.h>

/*
 * Arena wrappers — arena.h functions are static inline, so we expose them here
 */

Arena *glue_arena_create(unsigned int capacity)
{
	return arena_create((u64)capacity);
}

void *glue_arena_push(Arena *arena, unsigned int size)
{
	return arena_push(arena, (u64)size);
}

void glue_arena_clear(Arena *arena)
{
	arena_clear(arena);
}

void glue_arena_destroy(Arena *arena)
{
	arena_destroy(arena);
}

/*
 * Variadic wrappers — WASM can't handle ... so we take double* + count
 */

double glue_add(double *vals, int count)
{
	double total = 0.0;
	for (int i = 0; i < count; i++)
		total += vals[i];
	return total;
}

double glue_subtract(double *vals, int count)
{
	if (count == 0) return 0.0;
	double total = vals[0];
	for (int i = 1; i < count; i++)
		total -= vals[i];
	return total;
}

double glue_multiply(double *vals, int count)
{
	if (count == 0) return 0.0;
	double total = vals[0];
	for (int i = 1; i < count; i++)
		total *= vals[i];
	return total;
}

double glue_divide(double *vals, int count)
{
	if (count == 0) return 0.0;
	double total = vals[0];
	for (int i = 1; i < count; i++)
		total /= vals[i];
	return total;
}

float glue_min(double *vals, int count)
{
	if (count == 0) return 0.0f;
	float result = (float)vals[0];
	for (int i = 1; i < count; i++)
	{
		float v = (float)vals[i];
		if (v < result) result = v;
	}
	return result;
}

float glue_max(double *vals, int count)
{
	if (count == 0) return 0.0f;
	float result = (float)vals[0];
	for (int i = 1; i < count; i++)
	{
		float v = (float)vals[i];
		if (v > result) result = v;
	}
	return result;
}

/*
 * dense_forward wrapper — handles double **cache via a global
 */

static double *g_cache_ptr = NULL;

double *glue_dense_forward(Arena *arena, double *input, double *weights,
                           int m, int n, int p, int act)
{
	g_cache_ptr = NULL;
	double *result = dense_forward(arena, input, weights, m, n, p,
	                               (ActivationType)act, &g_cache_ptr);
	return result;
}

double *glue_get_cache_ptr()
{
	return g_cache_ptr;
}

/*
 * dense_backward wrapper — handles LayerGrad struct return via out pointers
 */

static double *g_dw_ptr = NULL;
static double *g_di_ptr = NULL;

void glue_dense_backward(Arena *arena, double *dout, double *input,
                         double *weights, double *cache,
                         int m, int n, int p, int act)
{
	LayerGrad grad = dense_backward(arena, dout, input, weights, cache,
	                                m, n, p, (ActivationType)act);
	g_dw_ptr = grad.d_weights;
	g_di_ptr = grad.d_input;
}

double *glue_get_dw_ptr()
{
	return g_dw_ptr;
}

double *glue_get_di_ptr()
{
	return g_di_ptr;
}

/*
 * Expose free() for init_weights cleanup
 */

void glue_free(void *ptr)
{
	free(ptr);
}
