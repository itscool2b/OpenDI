# sgd_update

## Synopsis

```c
#include "optimizers/sgd_update.h"

double *sgd_update(Arena *arena, double *weights, double *grads, double lr, int n);
```

## Description

Performs a Stochastic Gradient Descent (SGD) weight update.

The update rule is:
```
result[i] = weights[i] - lr * grads[i]
```

SGD is the simplest and most fundamental optimizer for training neural networks.

## Parameters

- `arena`: Arena allocator for memory
- `weights`: Pointer to the current weight values
- `grads`: Pointer to the gradients
- `lr`: Learning rate (step size)
- `n`: Number of elements

## Return Value

A pointer to memory in the arena containing the updated weights.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double weights[] = {1.0, 2.0, 3.0};
double grads[] = {0.1, 0.2, 0.3};
double *new_weights = sgd_update(arena, weights, grads, 0.01, 3);
// new_weights: {0.999, 1.998, 2.997}

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

A typical learning rate is between 0.001 and 0.1.

## See Also

mse_loss(3), cross_entropy(3), arena_create(3)
