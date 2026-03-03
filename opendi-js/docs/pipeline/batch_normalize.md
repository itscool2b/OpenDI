# batchNormalize

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.batchNormalize(features, nSamples, nFeatures)
```

## Description

Applies Z-score normalization to each feature column of a sample matrix independently.

For each column, computes `(x - mean) / std` so that each feature has mean ~0 and std ~1.

Wraps the C `batch_normalize()` function.

## Parameters

- `features`: Flat array of numbers (nSamples * nFeatures elements, row-major)
- `nSamples`: Number of rows (samples)
- `nFeatures`: Number of columns (features)

## Return Value

A `Float64Array` of length nSamples * nFeatures with normalized values.

## Example

```js
o.batchNormalize([1,2,3,4,5,6], 3, 2)
// Normalizes column 0: [1,3,5] and column 1: [2,4,6] independently
```

## Notes

Memory is automatically managed via a temporary arena.

For normalizing a single vector, use `normalize()`.

## See Also

normalize(3), denseForward(3)
