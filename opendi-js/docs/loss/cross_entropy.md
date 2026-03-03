# crossEntropy

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.crossEntropy(pred, targets)
```

## Description

Computes the cross-entropy loss between predictions and targets.

Used for multi-class classification tasks, typically paired with softmax output.

Wraps the C `cross_entropy()` function.

## Parameters

- `pred`: Predicted probabilities (array of numbers)
- `targets`: Target values (array of numbers, same length as pred)

## Return Value

The cross-entropy loss as a `number`.

## Example

```js
const pred = [0.7, 0.2, 0.1]
const targets = [1, 0, 0]
o.crossEntropy(pred, targets)    // cross-entropy value
```

## Notes

Memory is automatically managed via a temporary arena.

For the gradient, use `crossEntropyBackward()`.

When using softmax + cross-entropy together, use `ACTIVATION_SOFTMAX` in `denseForward()` and `ACTIVATION_NONE` in `denseBackward()` with `crossEntropyBackward()` for the combined gradient.

## See Also

mseLoss(3), crossEntropyBackward(3), softmax(3)
