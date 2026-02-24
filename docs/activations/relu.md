# relu

## Synopsis

```c
#include "activations/relu.h"

double relu(double x);
```

## Description

Computes the Rectified Linear Unit (ReLU) activation function.

The ReLU function is defined as:
```
relu(x) = max(0, x)
```

It returns the input value if it is positive, and 0 otherwise. ReLU is widely used in neural networks due to its computational efficiency and ability to mitigate the vanishing gradient problem.

## Parameters

- `x`: Input value

## Return Value

`x` if `x > 0`, otherwise `0`.

## Example

```c
double result1 = relu(5.0);     // Returns 5.0
double result2 = relu(-3.0);    // Returns 0.0
double result3 = relu(0.0);     // Returns 0.0
double result4 = relu(100.0);   // Returns 100.0
double result5 = relu(-100.0);  // Returns 0.0
```

## Notes

- ReLU is not differentiable at x = 0, but in practice this is rarely an issue
- The function is computationally efficient (simple comparison and return)
- Commonly used as the default activation function in hidden layers of neural networks

## See Also

sigmoid(3), softmax(3)
