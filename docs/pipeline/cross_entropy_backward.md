# cross_entropy_backward

## Synopsis

```c
#include "pipeline/cross_entropy_backward.h"

double *cross_entropy_backward(Arena *arena, double *pred, double *targets, int n_samples, int n_classes);
```

## Description

Computes the combined softmax + cross-entropy gradient with respect to pre-softmax logits.

The gradient is:
```
grad[i] = (pred[i] - targets[i]) / n_samples
```

This is the simplified gradient when softmax activation is combined with cross-entropy loss, avoiding the need for a separate `softmax_backward()` call.

## Parameters

- `arena`: Arena allocator for memory
- `pred`: Pointer to the softmax predictions (n_samples x n_classes)
- `targets`: Pointer to the one-hot targets (n_samples x n_classes)
- `n_samples`: Number of samples
- `n_classes`: Number of classes

## Return Value

A pointer to memory in the arena containing the gradient (n_samples x n_classes).

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double pred[] = {0.7, 0.2, 0.1};
double targets[] = {1.0, 0.0, 0.0};
double *grad = cross_entropy_backward(arena, pred, targets, 1, 3);
// grad: {-0.3, 0.2, 0.1}

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

Use `ACTIVATION_NONE` in `dense_backward()` when pairing with this function, since the activation gradient is already incorporated.

## See Also

cross_entropy(3), mse_backward(3), dense_backward(3)
