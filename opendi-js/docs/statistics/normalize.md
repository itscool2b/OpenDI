# normalize

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.normalize(arr)
```

## Description

Applies Z-score normalization to a vector. Each element is transformed to `(x - mean) / std`, producing output with mean approximately 0 and standard deviation approximately 1.

Wraps the C `normalize()` function.

## Parameters

- `arr`: An array of numbers

## Return Value

A `Float64Array` containing the normalized values.

## Example

```js
const norm = o.normalize([2, 4, 4, 4, 5, 5, 7, 9])
// mean of norm ≈ 0
// std of norm ≈ 1
```

## Notes

Memory is automatically managed via a temporary arena.

For normalizing feature columns in a batch, use `batchNormalize()`.

## See Also

batchNormalize(3)
