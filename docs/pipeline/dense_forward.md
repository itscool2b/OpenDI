# dense_forward

## Synopsis

```c
#include "pipeline/dense_forward.h"

double *dense_forward(Arena *arena, double *input, double *weights, int m, int n, int p, ActivationType act, double **cache);
```

## Description

Performs a dense (fully connected) layer forward pass: matrix multiplication followed by an activation function.

Computes `activation(input @ weights)` where input is m x n and weights is n x p, producing an m x p output.

Supported activations:
- `ACTIVATION_NONE`: No activation (linear layer)
- `ACTIVATION_RELU`: ReLU, cache stores pre-activation z
- `ACTIVATION_SIGMOID`: Sigmoid, cache stores post-activation output
- `ACTIVATION_SOFTMAX`: Per-row softmax, no cache needed

## Parameters

- `arena`: Arena allocator for memory
- `input`: Pointer to input matrix (m x n, row-major)
- `weights`: Pointer to weight matrix (n x p, row-major)
- `m`: Number of input rows (samples)
- `n`: Number of input columns (input features)
- `p`: Number of output columns (output features)
- `act`: Activation type to apply after matmul
- `cache`: Optional pointer to store values needed for backward pass. Pass NULL if not needed

## Return Value

A pointer to memory in the arena containing the m x p output matrix.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(65536);

double input[] = {1.0, 2.0, 3.0, 4.0};  // 2x2
double weights[] = {0.5, 0.5};            // 2x1
double *cache;

double *pred = dense_forward(arena, input, weights, 2, 2, 1, ACTIVATION_SIGMOID, &cache);
// pred contains sigmoid(matmul(input, weights))

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

Cache semantics differ per activation:
- RELU: cache = pre-activation z (needed by `relu_backward`)
- SIGMOID: cache = post-activation output (needed by `sigmoid_backward`)
- SOFTMAX: cache = NULL (use `cross_entropy_backward` for combined gradient)

For softmax + cross-entropy, use `ACTIVATION_SOFTMAX` here and `ACTIVATION_NONE` in `dense_backward()`.

## See Also

dense_backward(3), matmul(3), batch_relu(3), batch_sigmoid(3), batch_softmax(3)
