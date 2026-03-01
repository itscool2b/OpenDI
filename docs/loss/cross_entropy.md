# cross_entropy

## Synopsis

```c
#include "loss/cross_entropy.h"

double cross_entropy(double *predictions, double *targets, int n);
```

## Description

Computes the cross-entropy loss between predictions and targets.

The cross-entropy loss is defined as:
```
CE = -(1/n) * sum(targets[i] * log(predictions[i] + 1e-15))
```

A small epsilon (1e-15) is added to predictions to avoid taking the log of zero. Cross-entropy is the standard loss function for classification tasks.

## Parameters

- `predictions`: Pointer to the predicted probabilities
- `targets`: Pointer to the target labels (typically one-hot encoded)
- `n`: Number of elements

## Return Value

The cross-entropy loss as a double. Lower values indicate better predictions.

## Example

```c
double pred[] = {0.7, 0.2, 0.1};
double targ[] = {1.0, 0.0, 0.0};
double loss = cross_entropy(pred, targ, 3);
// loss ~ 0.1189
```

## Notes

No arena allocation is needed since this function returns a scalar.

Predictions should be in the range (0, 1]. The epsilon prevents numerical issues when predictions are exactly 0.

## See Also

mse_loss(3), softmax(3)
