# absolute

## Synopsis

```c
#include "primitive/absolute.h"

float absolute(float x);
```

## Description

Returns the absolute value of a floating-point number.

## Parameters

- `x`: Input value

## Return Value

The absolute value of `x` as a `float`.

## Example

```c
float result = absolute(-5.5f);  // Returns 5.5
float result2 = absolute(3.0f);  // Returns 3.0
float result3 = absolute(0.0f);  // Returns 0.0
```
