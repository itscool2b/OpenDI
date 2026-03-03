# vecdot

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.vecdot(a, b)
```

## Description

Computes the dot product of two vectors (sum of element-wise products).

Wraps the C `vecdot()` function. Both vectors must have the same length.

## Parameters

- `a`: First vector (array of numbers)
- `b`: Second vector (array of numbers)

## Return Value

The dot product as a `number`.

## Example

```js
o.vecdot([1, 2, 3], [4, 5, 6])    // 32 (1*4 + 2*5 + 3*6)
o.vecdot([1, 0], [0, 1])          // 0 (orthogonal)
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

vecadd(3), veccross(3), vecnorm(3), matmul(3)
