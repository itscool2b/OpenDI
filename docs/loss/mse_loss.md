# mse_loss

## Synopsis

```c
#include "loss/mse_loss.h"

double mse_loss(double *predictions, double *targets, int n);
```

## Description

Computes the Mean Squared Error (MSE) loss between predictions and targets.

The MSE loss is defined as:
```
MSE = (1/n) * sum((predictions[i] - targets[i])^2)
```

MSE is the most common loss function for regression tasks. It penalizes larger errors more heavily due to the squaring operation.

## Parameters

- `predictions`: Pointer to the predicted values
- `targets`: Pointer to the target (ground truth) values
- `n`: Number of elements

## Return Value

The mean squared error as a double. Returns 0.0 when predictions exactly match targets.

## Example

```c
double pred[] = {1.0, 2.0, 3.0};
double targ[] = {1.5, 2.5, 3.5};
double loss = mse_loss(pred, targ, 3);
// loss = (0.25 + 0.25 + 0.25) / 3 = 0.25
```

## Notes

No arena allocation is needed since this function returns a scalar.

The function is symmetric: `mse_loss(a, b, n) == mse_loss(b, a, n)`.

## See Also

cross_entropy(3)
