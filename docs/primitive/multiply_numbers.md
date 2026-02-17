# multiply_numbers

## Synopsis

```c
#include "primitive/multiply.h"

double multiply_numbers(int count, ...);
```

## Description

Multiplies a variable number of double-precision floating-point values.

## Parameters

- `count`: Number of values to multiply
- `...`: Variable list of double values

## Return Value

The product of all input values as a `double`.

## Example

```c
double result = multiply_numbers(3, 2.0, 3.0, 4.0);  // Returns 24.0
```
