# sigmoid

## Synopsis

```c
#include "activations/sigmoid.h"

double sigmoid(double x);
```

## Description

Computes the sigmoid (logistic) function of a value.

The sigmoid function is defined as:
```
sigmoid(x) = 1 / (1 + e^(-x))
```

It maps any real-valued number to a value between 0 and 1, making it useful for binary classification and as an activation function in neural networks.

## Parameters

- `x`: Input value

## Return Value

The sigmoid of `x` as a `double`, in the range (0, 1).

## Example

```c
double result1 = sigmoid(0.0);    // Returns 0.5
double result2 = sigmoid(2.0);    // Returns ~0.881
double result3 = sigmoid(-2.0);   // Returns ~0.119
double result4 = sigmoid(10.0);   // Returns ~0.99995
double result5 = sigmoid(-10.0);  // Returns ~0.00005
```

## Notes

- As x approaches +∞, sigmoid(x) approaches 1
- As x approaches -∞, sigmoid(x) approaches 0
- sigmoid(0) = 0.5 exactly
- The function is symmetric: sigmoid(-x) = 1 - sigmoid(x)

## See Also

relu(3), softmax(3)
