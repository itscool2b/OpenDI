# mseBackward

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.mseBackward(pred, targets)
```

## Description

Computes the gradient of the MSE loss with respect to predictions.

The gradient for each element is `2 * (pred[i] - targets[i]) / n`.

Wraps the C `mse_backward()` function.

## Parameters

- `pred`: Predicted values (array of numbers)
- `targets`: Target values (array of numbers, same length)

## Return Value

A `Float64Array` containing the MSE gradient.

## Example

```js
o.mseBackward([1, 0], [0, 1])
// Float64Array [1, -1] (scaled by 2/n)
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

mseLoss(3), crossEntropyBackward(3), denseBackward(3)
