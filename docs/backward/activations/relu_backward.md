# relu_backward

## Synopsis

```c
#include "backward/activations/relu_backward.h"

double *relu_backward(Arena *arena, double *dout, double *input, int n);
```

## Description

Computes the gradient of the ReLU activation function.

The ReLU backward pass is defined as:
```
grad[i] = (input[i] > 0) ? dout[i] : 0.0
```

The gradient passes through unchanged where the input was positive, and is zeroed where the input was zero or negative.

## Parameters

- `arena`: Arena allocator for memory
- `dout`: Pointer to the upstream gradient
- `input`: Pointer to the original input to the ReLU forward pass
- `n`: Number of elements

## Return Value

A pointer to memory in the arena containing the gradient.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double dout[] = {1.0, 2.0, 3.0};
double input[] = {0.5, -1.0, 2.0};
double *grad = relu_backward(arena, dout, input, 3);
// grad: {1.0, 0.0, 3.0}

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

The gradient at exactly input=0 is 0 (subgradient convention).

## See Also

relu(3), sigmoid_backward(3), softmax_backward(3)
