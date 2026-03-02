# dense_backward

## Synopsis

```c
#include "pipeline/dense_backward.h"

LayerGrad dense_backward(Arena *arena, double *dout, double *input, double *weights, double *cache, int m, int n, int p, ActivationType act);
```

## Description

Performs a dense (fully connected) layer backward pass: activation gradient followed by matrix multiplication gradients.

Computes gradients with respect to both weights and input:
1. Apply activation backward (if not `ACTIVATION_NONE`)
2. `d_weights = input^T @ d_act` (via `matmul_backward_b`)
3. `d_input = d_act @ weights^T` (via `matmul_backward_a`)

## Parameters

- `arena`: Arena allocator for memory
- `dout`: Pointer to upstream gradient (m x p)
- `input`: Pointer to the original forward input (m x n)
- `weights`: Pointer to the weight matrix (n x p)
- `cache`: Cached values from `dense_forward` (activation-specific)
- `m`: Number of rows (samples)
- `n`: Number of input features
- `p`: Number of output features
- `act`: Activation type used in the forward pass

## Return Value

A `LayerGrad` struct containing:
- `d_weights`: Gradient with respect to weights (n x p)
- `d_input`: Gradient with respect to input (m x n)

## Example

```c
Arena *arena = arena_create(65536);

double *cache;
double *pred = dense_forward(arena, input, weights, m, n, p, ACTIVATION_RELU, &cache);

double *dout = mse_backward(arena, pred, targets, m * p);
LayerGrad grad = dense_backward(arena, dout, input, weights, cache, m, n, p, ACTIVATION_RELU);

double *new_w = sgd_update(arena, weights, grad.d_weights, lr, n * p);

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

Use `ACTIVATION_NONE` when the loss backward already accounts for the activation gradient (e.g. softmax + cross-entropy combined gradient via `cross_entropy_backward`).

## See Also

dense_forward(3), relu_backward(3), sigmoid_backward(3), matmul_backward_a(3), matmul_backward_b(3)
