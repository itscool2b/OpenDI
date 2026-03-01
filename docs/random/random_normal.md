# random_normal

## Synopsis

```c
#include "random/random_normal.h"

double *random_normal(Arena *arena, double mean, double std, int n);
```

## Description

Generates an array of normally distributed random numbers using the Box-Muller transform.

Each element is computed as:
```
u1, u2 = uniform random in (0, 1)
z = sqrt(-2 * log(u1)) * cos(2 * PI * u2)
result[i] = mean + std * z
```

Gaussian initialization generally produces better training results than uniform initialization for neural network weights.

## Parameters

- `arena`: Arena allocator for memory
- `mean`: Mean of the normal distribution
- `std`: Standard deviation of the normal distribution
- `n`: Number of random values to generate

## Return Value

A pointer to memory in the arena containing `n` normally distributed random doubles.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

random_seed(42);
double *weights = random_normal(arena, 0.0, 0.01, 10);
// weights contains 10 values from N(0, 0.01)

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

Use `random_seed()` before calling this function for reproducible results.

## See Also

random_uniform(3), random_seed(3), arena_create(3)
