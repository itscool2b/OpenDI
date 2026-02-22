# vecscale

## Synopsis

```c
#include "linalg/vectors/vecscale.h"

double *vecscale(Arena *arena, const double *arr, double scalar, size_t length);
```

## Description

Scales (multiplies) a vector by a scalar value.

Multiplies each element of the input vector by the given scalar:
- `result[i] = arr[i] × scalar` for all `i` from `0` to `length-1`

## Parameters

- `arena`: Arena allocator for memory
- `arr`: Pointer to the input vector
- `scalar`: The scaling factor
- `length`: Number of elements in the vector

## Return Value

A pointer to memory in the arena containing the scaled vector.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

double v[] = {1.0, 2.0, 3.0};

// Basic scaling
double *result = vecscale(arena, v, 2.0, 3);
// result contains: {2.0, 4.0, 6.0}

// Scale by 0 (zero vector)
double *zero = vecscale(arena, v, 0.0, 3);
// zero contains: {0.0, 0.0, 0.0}

// Negation
double *neg = vecscale(arena, v, -1.0, 3);
// neg contains: {-1.0, -2.0, -3.0}

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

Special scalar values:
- `scalar = 1`: Returns a copy of the original vector
- `scalar = 0`: Returns a zero vector
- `scalar = -1`: Returns the negation of the vector

Properties:
- Associative: `a × (b × v) = (a × b) × v`
- Distributive: `s × (v₁ + v₂) = s × v₁ + s × v₂`

## See Also

vecadd(3), vecnorm(3), arena_create(3), arena_destroy(3)
