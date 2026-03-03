# vecadd

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.vecadd(a, b)
```

## Description

Computes the element-wise sum of two vectors.

Wraps the C `vecadd()` function. Both vectors must have the same length.

## Parameters

- `a`: First vector (array of numbers)
- `b`: Second vector (array of numbers)

## Return Value

A `Float64Array` containing the element-wise sum.

## Example

```js
o.vecadd([1, 2, 3], [4, 5, 6])    // Float64Array [5, 7, 9]
o.vecadd([0, 0], [1, 1])          // Float64Array [1, 1]
```

## Notes

Memory is automatically managed via a temporary arena.

The length is inferred from the first array.

## See Also

vecscale(3), vecdot(3), veccross(3), vecnorm(3), matadd(3)
