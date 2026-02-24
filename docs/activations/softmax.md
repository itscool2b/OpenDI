# softmax

## Synopsis

```c
#include "activations/softmax.h"

double *softmax(Arena *arena, double *v, int n);
```

## Description

Computes the softmax function for a vector of values.

The softmax function converts a vector of values into a probability distribution. Each element is transformed to a value between 0 and 1, and all elements sum to 1.

The softmax for element i is defined as:
```
softmax(v[i]) = e^(v[i] - max) / sum(e^(v[j] - max) for all j)
```

Where `max` is the maximum value in the input vector (used for numerical stability).

## Parameters

- `arena`: Arena allocator for memory
- `v`: Pointer to the input vector
- `n`: Number of elements in the vector

## Return Value

A pointer to memory in the arena containing the softmax probabilities.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double v[] = {1.0, 2.0, 3.0};
double *result = softmax(arena, v, 3);
// result now contains: ~{0.090, 0.245, 0.665}
// sum of result = 1.0

// For equal values, uniform distribution
double v2[] = {1.0, 1.0, 1.0};
double *result2 = softmax(arena, v2, 3);
// result2 now contains: ~{0.333, 0.333, 0.333}

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

The input vector `v` must have at least `n` elements.

Numerical stability is ensured by subtracting the maximum value before exponentiation.

## See Also

sigmoid(3), relu(3), arena_create(3), arena_destroy(3)
