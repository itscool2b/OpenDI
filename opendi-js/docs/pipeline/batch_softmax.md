# batchSoftmax

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.batchSoftmax(input, rows, cols)
```

## Description

Applies softmax independently to each row of a matrix.

Each row is converted to a probability distribution (values in [0, 1], summing to 1).

Wraps the C `batch_softmax()` function.

## Parameters

- `input`: Flat array of numbers (rows * cols elements, row-major)
- `rows`: Number of rows (samples)
- `cols`: Number of columns (classes)

## Return Value

A `Float64Array` of length rows * cols with per-row softmax probabilities.

## Example

```js
o.batchSoftmax([1,2,3, 1,1,1], 2, 3)
// Row 0: softmax([1,2,3]) ≈ [0.09, 0.24, 0.67]
// Row 1: softmax([1,1,1]) ≈ [0.33, 0.33, 0.33]
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

softmax(3), batchRelu(3), batchSigmoid(3), crossEntropyBackward(3)
