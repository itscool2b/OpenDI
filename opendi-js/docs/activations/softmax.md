# softmax

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.softmax(arr)
```

## Description

Computes the softmax function for a vector of values, converting them into a probability distribution.

Each element is transformed to a value between 0 and 1, and all elements sum to 1. The maximum value is subtracted before exponentiation for numerical stability.

Wraps the C `softmax()` function.

## Parameters

- `arr`: An array of numbers

## Return Value

A `Float64Array` containing the softmax probabilities. All values are in [0, 1] and sum to 1.

## Example

```js
const sm = o.softmax([1, 2, 3])
// sm ≈ [0.090, 0.245, 0.665]
// sm[0] + sm[1] + sm[2] === 1.0

const uniform = o.softmax([1, 1, 1])
// uniform ≈ [0.333, 0.333, 0.333]
```

## Notes

Memory is automatically managed via a temporary arena.

For batch softmax across multiple rows, use `batchSoftmax()`.

## See Also

relu(3), sigmoid(3), batchSoftmax(3), softmaxBackward(3)
