# mseLoss

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.mseLoss(pred, targets)
```

## Description

Computes the Mean Squared Error loss between predictions and targets.

MSE = (1/n) * sum((pred[i] - targets[i])^2)

Wraps the C `mse_loss()` function.

## Parameters

- `pred`: Predicted values (array of numbers)
- `targets`: Target values (array of numbers, same length as pred)

## Return Value

The MSE loss as a `number`.

## Example

```js
o.mseLoss([1, 2, 3], [1, 2, 3])    // 0 (perfect prediction)
o.mseLoss([1, 0], [0, 1])          // 1.0
```

## Notes

Memory is automatically managed via a temporary arena.

For the gradient, use `mseBackward()`.

## See Also

crossEntropy(3), mseBackward(3)
