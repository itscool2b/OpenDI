# accuracy

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.accuracy(pred, labels, nSamples, nClasses)
```

## Description

Computes classification accuracy by comparing predicted class probabilities against integer labels.

For each sample, the predicted class is the column with the highest probability. Accuracy is the fraction of correct predictions.

Wraps the C `accuracy()` function.

## Parameters

- `pred`: Predicted probabilities (flat array, nSamples * nClasses elements, row-major)
- `labels`: True integer labels (array of integers, nSamples elements)
- `nSamples`: Number of samples
- `nClasses`: Number of classes

## Return Value

The accuracy as a `number` in [0, 1].

## Example

```js
const pred = [0.9, 0.1, 0.2, 0.8]  // 2 samples, 2 classes
const labels = [0, 1]               // correct labels
o.accuracy(pred, labels, 2, 2)      // 1.0 (both correct)
```

## Notes

Memory is automatically managed via a temporary arena.

Labels are passed as an `Int32Array` internally.

## See Also

crossEntropy(3), crossEntropyBackward(3), denseForward(3)
