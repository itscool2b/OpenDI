# mse_backward

## Synopsis

```c
#include "pipeline/mse_backward.h"

double *mse_backward(Arena *arena, double *pred, double *targets, int n);
```

## Description

Computes the gradient of the mean squared error loss with respect to predictions.

The gradient is:
```
grad[i] = 2 * (pred[i] - targets[i]) / n
```

## Parameters

- `arena`: Arena allocator for memory
- `pred`: Pointer to the predictions array
- `targets`: Pointer to the targets array
- `n`: Number of elements

## Return Value

A pointer to memory in the arena containing the gradient.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double pred[] = {0.8, 0.3};
double targets[] = {1.0, 0.0};
double *grad = mse_backward(arena, pred, targets, 2);
// grad: {-0.2, 0.3}

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

This gradient is typically passed to `sigmoid_backward()` or used directly in `dense_backward()`.

## See Also

mse_loss(3), cross_entropy_backward(3), dense_backward(3)
