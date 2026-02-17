# minmax

## Synopsis

```c
#include "primitive/minmax.h"

float minmax(int decision, int count, ...);
```

## Description

Finds the minimum or maximum value from a list of floating-point numbers.

## Parameters

- `decision`: Operation selector (0 for minimum, 1 for maximum)
- `count`: Number of values to compare
- `...`: Variable list of float values

## Return Value

The minimum or maximum value as a `float`.

Returns `NAN` if `count` is 0.

## Example

```c
float min_val = minmax(0, 3, 5.0f, 2.0f, 8.0f);  // Returns 2.0
float max_val = minmax(1, 3, 5.0f, 2.0f, 8.0f);  // Returns 8.0
float single = minmax(0, 1, 42.0f);              // Returns 42.0
float empty = minmax(0, 0);                       // Returns NAN
```
