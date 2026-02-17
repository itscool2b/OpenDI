# romberg_integrate

## Synopsis

```c
#include "calculus/romberg.h"

double romberg_integrate(double (*f)(double), double a, double b, double eps, int k_max);
```

## Description

Computes the definite integral of a function using Romberg integration.

Romberg integration combines the trapezoidal rule with Richardson extrapolation to achieve high accuracy with fewer function evaluations. It builds a triangular array of approximations and refines them iteratively.

## Parameters

- `f`: Pointer to the function to integrate
- `a`: Lower bound of integration
- `b`: Upper bound of integration
- `eps`: Desired precision (stopping criterion)
- `k_max`: Maximum number of refinement iterations

## Return Value

The approximate definite integral of `f` from `a` to `b`.

Returns `0.0` if `a` equals `b` (zero-width interval).

Returns negative of the integral if `b` < `a` (reversed interval).

## Example

```c
// f(x) = x^2, integral from 0 to 1 = 1/3
double f(double x) { return x * x; }
double result = romberg_integrate(f, 0.0, 1.0, 1e-10, 20);  // ≈ 0.333...

// f(x) = sin(x), integral from 0 to pi = 2
double g(double x) { return sin(x); }
double result2 = romberg_integrate(g, 0.0, M_PI, 1e-10, 20);  // ≈ 2.0

// f(x) = e^x, integral from 0 to 1 = e - 1
double h(double x) { return exp(x); }
double result3 = romberg_integrate(h, 0.0, 1.0, 1e-10, 20);  // ≈ 1.718...
```

## Notes

- High-order accurate (error reduces as O(h^(2n)) where n is the iteration)
- More efficient than Simpson's rule for smooth functions
- Memory-safe implementation using dynamically allocated arrays
- Convergence is checked against the specified epsilon

## See Also

No related functions.
