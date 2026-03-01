# sigmoid_backward

## Synopsis

```c
#include "backward/activations/sigmoid_backward.h"

double *sigmoid_backward(Arena *arena, double *dout, double *output, int n);
```

## Description

Computes the gradient of the sigmoid activation function.

The sigmoid backward pass is defined as:
```
grad[i] = dout[i] * output[i] * (1.0 - output[i])
```

This uses the sigmoid output (not the input) since the derivative of sigmoid can be expressed in terms of its output: `sigmoid'(x) = sigmoid(x) * (1 - sigmoid(x))`.

## Parameters

- `arena`: Arena allocator for memory
- `dout`: Pointer to the upstream gradient
- `output`: Pointer to the sigmoid forward pass output
- `n`: Number of elements

## Return Value

A pointer to memory in the arena containing the gradient.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double dout[] = {1.0, 1.0};
double output[] = {0.5, 0.73};
double *grad = sigmoid_backward(arena, dout, output, 2);
// grad: {0.25, 0.1971}

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

The maximum gradient occurs when the sigmoid output is 0.5 (gradient = 0.25).

## See Also

sigmoid(3), relu_backward(3), softmax_backward(3)
