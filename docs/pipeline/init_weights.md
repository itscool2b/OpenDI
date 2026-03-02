# init_weights

## Synopsis

```c
#include "pipeline/init_weights.h"

double *init_weights(int n, double mean, double std);
```

## Description

Initializes a weight array with random values drawn from a normal distribution. Creates a temporary arena internally, generates values with `random_normal()`, copies to a `malloc`'d array, and destroys the temporary arena.

## Parameters

- `n`: Number of weights to initialize
- `mean`: Mean of the normal distribution
- `std`: Standard deviation of the normal distribution

## Return Value

A pointer to a `malloc`'d array of n doubles. The caller must `free()` this pointer when done.

Returns `NULL` if allocation fails.

## Example

```c
random_seed(42);
double *weights = init_weights(784 * 128, 0.0, 0.05);

// ... use weights in training loop ...

free(weights);
```

## Notes

The returned array is heap-allocated with `malloc`, not arena-allocated. This allows weights to survive `arena_clear()` calls during training.

Call `random_seed()` before `init_weights()` for reproducible initialization.

## See Also

random_normal(3), random_seed(3), dense_forward(3)
