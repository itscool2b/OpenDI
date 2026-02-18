# vecdot

## Synopsis

```c
#include "linalg/vectors/vecdot.h"

double vecdot(const double *vec1, const double *vec2, size_t length);
```

## Description

Computes the dot product (scalar product) of two vectors.

The dot product is the sum of the products of corresponding components. For vectors `vec1` and `vec2` of length `n`:
- `result = Σ(vec1[i] × vec2[i])` for `i = 0` to `n-1`

## Parameters

- `vec1`: Pointer to the first input vector
- `vec2`: Pointer to the second input vector
- `length`: Number of elements in each vector

## Return Value

The dot product as a `double`.

Returns `0.0` if `length` is 0.

## Example

```c
// Basic dot product
double v1[] = {1.0, 2.0, 3.0};
double v2[] = {4.0, 5.0, 6.0};
double result = vecdot(v1, v2, 3);  // Returns 32.0 (1×4 + 2×5 + 3×6)

// Perpendicular vectors (dot product is 0)
double i[] = {1.0, 0.0, 0.0};
double j[] = {0.0, 1.0, 0.0};
double ortho = vecdot(i, j, 3);     // Returns 0.0

// Vector with itself (gives squared norm)
double v[] = {3.0, 4.0};
double self_dot = vecdot(v, v, 2);  // Returns 25.0 (3² + 4²)
```

## Notes

None.

Properties of the dot product:
- Commutative: `a · b = b · a`
- Distributive over addition: `a · (b + c) = a · b + a · c`
- Zero for perpendicular (orthogonal) vectors
- Equal to `|a||b|cos(θ)` where θ is the angle between vectors

## See Also

vecnorm(3), veccross(3)
