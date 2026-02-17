# central_difference

## Synopsis

```c
#include "calculus/centraldiff.h"

double central_difference(double (*f)(double), double x, double h);
```

## Description

Computes the first derivative using the central difference method.

**Formula:** f'(x) ≈ (f(x + h) - f(x - h)) / (2h)

## Parameters

- `f`: Pointer to the function to differentiate
- `x`: Point at which to evaluate the derivative
- `h`: Step size (should be small, e.g., 0.0001)

## Return Value

The approximate derivative at point `x`.

Returns `0.0` if `h` is 0.

## Example

```c
double f(double x) { return x * x; }
double result = central_difference(f, 3.0, 0.0001);  // ≈ 6.0
```

## Notes

- Second-order accurate (error proportional to h²)
- More accurate than forward or backward difference for the same h
- Symmetric and generally preferred for first derivatives

## See Also

forwarddiff(3), backwarddiff(3), secondderivative(3)
