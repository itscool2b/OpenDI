# random_uniform

## Synopsis

```c
#include "random/random_uniform.h"

double *random_uniform(Arena *arena, double min, double max, int n);
```

## Description

Generates an array of uniformly distributed random numbers in the range [min, max].

Each element is computed as:
```
result[i] = min + (max - min) * (rand() / RAND_MAX)
```

Useful for random weight initialization in neural networks.

## Parameters

- `arena`: Arena allocator for memory
- `min`: Minimum value (inclusive)
- `max`: Maximum value (inclusive)
- `n`: Number of random values to generate

## Return Value

A pointer to memory in the arena containing `n` random doubles in [min, max].

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

random_seed(42);
double *weights = random_uniform(arena, -1.0, 1.0, 10);
// weights contains 10 random values in [-1, 1]

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

Use `random_seed()` before calling this function for reproducible results.

## See Also

random_normal(3), random_seed(3), arena_create(3)
