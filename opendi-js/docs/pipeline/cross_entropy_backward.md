# crossEntropyBackward

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.crossEntropyBackward(pred, targets, nSamples, nClasses)
```

## Description

Computes the gradient of the cross-entropy loss with respect to predictions.

Wraps the C `cross_entropy_backward()` function.

## Parameters

- `pred`: Predicted probabilities (flat array, nSamples * nClasses elements)
- `targets`: Target values (flat array, nSamples * nClasses elements)
- `nSamples`: Number of samples
- `nClasses`: Number of classes

## Return Value

A `Float64Array` of length nSamples * nClasses containing the gradient.

## Example

```js
const grad = o.crossEntropyBackward(pred, targets, 4, 3)
```

## Notes

Memory is automatically managed via a temporary arena.

When using softmax + cross-entropy, the combined gradient simplifies to `pred - targets`. Use `ACTIVATION_SOFTMAX` in `denseForward()` and `ACTIVATION_NONE` in `denseBackward()`, then pass this gradient.

## See Also

crossEntropy(3), mseBackward(3), denseBackward(3), softmax(3)
