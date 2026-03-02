# accuracy

## Synopsis

```c
#include "pipeline/accuracy.h"

double accuracy(double *pred, int *labels, int n_samples, int n_classes);
```

## Description

Computes classification accuracy as the fraction of correct predictions.

For binary classification (n_classes=1), predictions are thresholded at 0.5. For multiclass (n_classes>1), the predicted class is the argmax of each row.

## Parameters

- `pred`: Pointer to predictions. For binary: array of n_samples values. For multiclass: n_samples x n_classes matrix
- `labels`: Pointer to integer labels (0-indexed class indices)
- `n_samples`: Number of samples
- `n_classes`: Number of classes (1 for binary)

## Return Value

A double in [0, 1] representing the fraction of correct predictions.

## Example

```c
// Binary classification
double pred[] = {0.9, 0.1, 0.8};
int labels[] = {1, 0, 1};
double acc = accuracy(pred, labels, 3, 1);
// acc: 1.0

// Multiclass classification
double pred2[] = {0.1, 0.8, 0.1,
                  0.9, 0.05, 0.05};
int labels2[] = {1, 0};
double acc2 = accuracy(pred2, labels2, 2, 3);
// acc2: 1.0
```

## Notes

Does not allocate memory. No arena required.

For binary classification, 0.5 maps to class 1.

## See Also

dense_forward(3), batch_softmax(3), batch_sigmoid(3)
