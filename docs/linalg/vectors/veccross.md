# veccross

## Synopsis

```c
#include "linalg/vectors/veccross.h"

double *veccross(Arena *arena, const double *vec1, const double *vec2);
```

## Description

Computes the cross product of two 3-dimensional vectors.

The cross product produces a vector that is perpendicular to both input vectors. For vectors `a = (a₁, a₂, a₃)` and `b = (b₁, b₂, b₃)`:
- `result[0] = a₂b₃ - a₃b₂`
- `result[1] = a₃b₁ - a₁b₃`
- `result[2] = a₁b₂ - a₂b₁`

## Parameters

- `arena`: Arena allocator for memory
- `vec1`: Pointer to the first 3D vector
- `vec2`: Pointer to the second 3D vector

## Return Value

A pointer to memory in the arena containing the 3-element cross product.

Returns `NULL` if arena allocation fails.

## Example

```c
Arena *arena = arena_create(1024);

// Standard basis vectors
double i[] = {1.0, 0.0, 0.0};  // x-axis
double j[] = {0.0, 1.0, 0.0};  // y-axis
double *k = veccross(arena, i, j);    // Returns {0.0, 0.0, 1.0} (z-axis)

// General case
double a[] = {1.0, 2.0, 3.0};
double b[] = {4.0, 5.0, 6.0};
double *result = veccross(arena, a, b);  // Returns {-3.0, 6.0, -3.0}

arena_destroy(arena);
```

## Notes

Memory is allocated from the arena. Use `arena_destroy()` or `arena_clear()` to free.

This function only works with 3-dimensional vectors.

Properties:
- Anti-commutative: `a × b = -(b × a)`
- Self-cross is zero: `a × a = 0`
- Perpendicular to both inputs

## See Also

vecdot(3), vecnorm(3), arena_create(3), arena_destroy(3)
