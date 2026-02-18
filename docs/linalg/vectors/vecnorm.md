# vecnorm

## Synopsis

```c
#include "linalg/vectors/vecnorm.h"

double vecnorm(const double *vec, size_t length);
```

## Description

Computes the Euclidean norm (magnitude, length) of a vector.

The norm is the square root of the sum of squared components:
- `||v|| = √(v₁² + v₂² + ... + vₙ²)`

This function uses `vecdot()` internally: `norm = sqrt(vecdot(vec, vec, length))`

## Parameters

- `vec`: Pointer to the input vector
- `length`: Number of elements in the vector

## Return Value

The Euclidean norm (magnitude) as a `double`.

Returns `0.0` if `length` is 0 or if the vector is a zero vector.

## Example

```c
// 3-4-5 triangle
double v1[] = {3.0, 4.0};
double n1 = vecnorm(v1, 2);   // Returns 5.0

// Unit vector
double v2[] = {1.0, 0.0, 0.0};
double n2 = vecnorm(v2, 3);   // Returns 1.0

// Zero vector
double v3[] = {0.0, 0.0, 0.0};
double n3 = vecnorm(v3, 3);   // Returns 0.0

// 3D vector
double v4[] = {1.0, 2.0, 2.0};
double n4 = vecnorm(v4, 3);   // Returns 3.0
```

## Notes

None.

Properties:
- Always non-negative: `||v|| ≥ 0`
- Zero only for zero vector: `||v|| = 0` iff `v = 0`
- Homogeneous: `||cv|| = |c|·||v||` for scalar `c`

## See Also

vecdot(3), vecscale(3)
