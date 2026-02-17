# secondderivative

## Synopsis

```c
#include "calculus/secondderivative.h"

double secondderivative(double (*f)(double), double x, double h);
```

## Description

Computes the second derivative using the central difference method.

**Formula:** f''(x) ≈ (f(x + h) - 2f(x) + f(x - h)) / h²

## Parameters

- `f`: Pointer to the function to differentiate
- `x`: Point at which to evaluate the second derivative
- `h`: Step size (should be small, e.g., 0.001)

## Return Value

The approximate second derivative at point `x`.

Returns `NAN` if `h` is 0.

## Example

```c
double f(double x) { return x * x; }           // f''(x) = 2
double result = secondderivative(f, 3.0, 0.001);  // ≈ 2.0

double g(double x) { return x * x * x; }       // f''(x) = 6x
double result2 = secondderivative(g, 2.0, 0.001); // ≈ 12.0
```

## Notes

Second derivatives require careful step size selection. Values larger than those used for first derivatives often produce better results due to cancellation effects.

## See Also

central_difference(3)
