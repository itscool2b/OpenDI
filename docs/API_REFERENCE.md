# OpenDI API Reference

This document provides a comprehensive reference for all functions available in the OpenDI library.

## Table of Contents

- [Primitive Operations](#primitive-operations)
- [Calculus](#calculus)

---

## Primitive Operations

The primitive operations module provides fundamental mathematical operations with support for variadic arguments.

### Addition

```c
#include "primitive/add.h"

double add_numbers(int count, ...);
```

Adds a variable number of double-precision floating-point values.

**Parameters:**
- `count`: Number of values to add
- `...`: Variable list of double values

**Returns:**
The sum of all input values as a `double`.

**Example:**
```c
double result = add_numbers(3, 1.0, 2.0, 3.0);  // Returns 6.0
```

---

### Subtraction

```c
#include "primitive/subtract.h"

double subtract_numbers(int count, ...);
```

Subtracts subsequent values from the first value.

**Parameters:**
- `count`: Number of values
- `...`: Variable list of double values. The first value is the minuend, all subsequent values are subtracted from it.

**Returns:**
The result of successive subtraction as a `double`.

**Example:**
```c
double result = subtract_numbers(3, 10.0, 3.0, 2.0);  // Returns 5.0 (10 - 3 - 2)
```

---

### Multiplication

```c
#include "primitive/multiply.h"

double multiply_numbers(int count, ...);
```

Multiplies a variable number of double-precision floating-point values.

**Parameters:**
- `count`: Number of values to multiply
- `...`: Variable list of double values

**Returns:**
The product of all input values as a `double`.

**Example:**
```c
double result = multiply_numbers(3, 2.0, 3.0, 4.0);  // Returns 24.0
```

---

### Division

```c
#include "primitive/divide.h"

double divide_numbers(int count, ...);
```

Divides the first value by all subsequent values in sequence.

**Parameters:**
- `count`: Number of values
- `...`: Variable list of double values. The first value is the dividend, all subsequent values are divisors.

**Returns:**
The result of successive division as a `double`. Returns `0.0` if:
- `count` is 0
- Any divisor is 0.0 (also prints error message)

**Example:**
```c
double result = divide_numbers(3, 24.0, 4.0, 2.0);  // Returns 3.0 (24 / 4 / 2)
```

---

### Absolute Value

```c
#include "primitive/absolute.h"

float absolute(float x);
```

Returns the absolute value of a floating-point number.

**Parameters:**
- `x`: Input value

**Returns:**
The absolute value of `x` as a `float`.

**Example:**
```c
float result = absolute(-5.5f);  // Returns 5.5
float result2 = absolute(3.0f);  // Returns 3.0
```

---

### Minimum and Maximum

```c
#include "primitive/minmax.h"

float minmax(int decision, int count, ...);
```

Finds the minimum or maximum value from a list of floating-point numbers.

**Parameters:**
- `decision`: Operation selector (0 for minimum, 1 for maximum)
- `count`: Number of values to compare
- `...`: Variable list of float values

**Returns:**
The minimum or maximum value as a `float`. Returns `NAN` if `count` is 0.

**Example:**
```c
float min_val = minmax(0, 3, 5.0f, 2.0f, 8.0f);   // Returns 2.0 (minimum)
float max_val = minmax(1, 3, 5.0f, 2.0f, 8.0f);   // Returns 8.0 (maximum)
```

---

### Rounding

```c
#include "primitive/rounding.h"

double roundval(const char* decision, double x);
```

Rounds a floating-point number using the specified rounding mode.

**Parameters:**
- `decision`: Rounding mode string ("floor" or "ceil")
- `x`: Value to round

**Returns:**
The rounded value as a `double`:
- `"floor"`: Returns the largest integer less than or equal to `x`
- `"ceil"`: Returns the smallest integer greater than or equal to `x`
- Any other string: Returns `x` unchanged

**Example:**
```c
double floor_result = roundval("floor", 3.7);   // Returns 3.0
double ceil_result = roundval("ceil", 3.2);     // Returns 4.0
double neg_floor = roundval("floor", -3.7);     // Returns -4.0
```

---

### Exponents

```c
#include "primitive/exponents.h"

double exponents(float value, float exponent);
```

Computes the power of a number.

**Parameters:**
- `value`: The base value
- `exponent`: The exponent

**Returns:**
`value` raised to the power of `exponent` as a `double`.

**Special Cases:**
- If both `value` and `exponent` are 0, returns 1.0 (mathematical convention)

**Example:**
```c
double result1 = exponents(2.0f, 3.0f);     // Returns 8.0 (2^3)
double result2 = exponents(4.0f, 0.5f);     // Returns 2.0 (square root)
double result3 = exponents(2.0f, -2.0f);    // Returns 0.25 (2^-2)
```

---

## Calculus

The calculus module provides numerical differentiation methods.

### Forward Difference

```c
#include "calculus/forwarddiff.h"

double forwarddiff(double (*f)(double), double x, double h);
```

Computes the first derivative using the forward difference method.

**Formula:** f'(x) ≈ (f(x + h) - f(x)) / h

**Parameters:**
- `f`: Pointer to the function to differentiate
- `x`: Point at which to evaluate the derivative
- `h`: Step size (should be small, e.g., 0.0001)

**Returns:**
The approximate derivative at point `x`. Returns `0.0` if `h` is 0.

**Error Characteristics:**
- First-order accurate (error proportional to h)
- Tends to overestimate the derivative

**Example:**
```c
double f(double x) { return x * x; }  // f(x) = x^2, f'(x) = 2x
double result = forwarddiff(f, 3.0, 0.0001);  // Returns approximately 6.0
```

---

### Backward Difference

```c
#include "calculus/backwarddiff.h"

double backwarddiff(double (*f)(double), double x, double h);
```

Computes the first derivative using the backward difference method.

**Formula:** f'(x) ≈ (f(x) - f(x - h)) / h

**Parameters:**
- `f`: Pointer to the function to differentiate
- `x`: Point at which to evaluate the derivative
- `h`: Step size (should be small, e.g., 0.0001)

**Returns:**
The approximate derivative at point `x`. Returns `NAN` if `h` is 0.

**Error Characteristics:**
- First-order accurate (error proportional to h)
- Tends to underestimate the derivative

**Example:**
```c
double f(double x) { return x * x; }  // f(x) = x^2, f'(x) = 2x
double result = backwarddiff(f, 3.0, 0.0001);  // Returns approximately 6.0
```

---

### Central Difference

```c
#include "calculus/centraldiff.h"

double central_difference(double (*f)(double), double x, double h);
```

Computes the first derivative using the central difference method.

**Formula:** f'(x) ≈ (f(x + h) - f(x - h)) / (2h)

**Parameters:**
- `f`: Pointer to the function to differentiate
- `x`: Point at which to evaluate the derivative
- `h`: Step size (should be small, e.g., 0.0001)

**Returns:**
The approximate derivative at point `x`. Returns `0.0` if `h` is 0.

**Error Characteristics:**
- Second-order accurate (error proportional to h^2)
- More accurate than forward or backward difference for the same h
- Symmetric and generally preferred for first derivatives

**Example:**
```c
double f(double x) { return x * x; }  // f(x) = x^2, f'(x) = 2x
double result = central_difference(f, 3.0, 0.0001);  // Returns approximately 6.0
```

---

### Second Derivative

```c
#include "calculus/secondderivative.h"

double secondderivative(double (*f)(double), double x, double h);
```

Computes the second derivative using the central difference method.

**Formula:** f''(x) ≈ (f(x + h) - 2f(x) + f(x - h)) / h^2

**Parameters:**
- `f`: Pointer to the function to differentiate
- `x`: Point at which to evaluate the second derivative
- `h`: Step size (should be small, e.g., 0.001)

**Returns:**
The approximate second derivative at point `x`. Returns `NAN` if `h` is 0.

**Example:**
```c
double f(double x) { return x * x; }  // f(x) = x^2, f''(x) = 2
double result = secondderivative(f, 3.0, 0.001);  // Returns approximately 2.0
```

---

## Numerical Considerations

### Step Size Selection

When using numerical differentiation methods, the choice of step size `h` is crucial:

- **Too large**: Truncation error dominates, leading to inaccurate results
- **Too small**: Round-off error dominates due to finite floating-point precision
- **Optimal**: Typically between 10^-4 and 10^-8 for double-precision arithmetic

For most applications, `h = 0.0001` provides a good balance for first derivatives.

### Error Analysis

| Method | Order of Accuracy | Error Term | Use Case |
|--------|------------------|------------|----------|
| Forward Difference | O(h) | ~h | One-sided information available |
| Backward Difference | O(h) | ~h | One-sided information available |
| Central Difference | O(h^2) | ~h^2 | Best accuracy for first derivatives |
| Second Derivative | O(h^2) | ~h^2 | Curvature analysis |

---

## Building and Testing

To compile programs using OpenDI:

```bash
gcc -I./include your_program.c src/primitive/add/add.c -o your_program -lm
```

To run the test suite:

```bash
# Compile all tests
mkdir -p test_bin
for test in tests/test_*.c; do
    name=$(basename $test .c)
    gcc -I./include $test src/*/*/*.c -o test_bin/$name -lm
done

# Run all tests
for test in test_bin/test_*; do
    ./$test
done
```

---

## License

See the project root for license information.
