# softmax_backward

## Synopsis

```c
#include "backward/activations/softmax_backward.h"

double *softmax_backward(Arena *arena, double *dout, double *output, int n);
```

## Description

Computes the gradient of the softmax activation function.

The softmax backward pass is defined as:
```
dot = sum(dout[i] * output[i])
grad[i] = output[i] * (dout[i] - dot)
```

This is the efficient form of the Jacobian-vector product for softmax.

## Parameters

- `arena`: Arena allocator for memory
- `dout`: Pointer to the upstream gradient
- `output`: Pointer to the softmax forward pass output
- `n`: Number of elements

## Return Value

A pointer to memory in the arena containing the gradient.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double dout[] = {1.0, 0.0, 0.0};
double output[] = {0.5, 0.3, 0.2};
double *grad = softmax_backward(arena, dout, output, 3);
// grad: {0.25, -0.15, -0.10}

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

The gradients always sum to zero, which is a property of the softmax function.

## See Also

softmax(3), relu_backward(3), sigmoid_backward(3)
