# veccross

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.veccross(a, b)
```

## Description

Computes the cross product of two 3D vectors.

Wraps the C `veccross()` function. Both vectors must have exactly 3 elements.

## Parameters

- `a`: First 3D vector (array of 3 numbers)
- `b`: Second 3D vector (array of 3 numbers)

## Return Value

A `Float64Array` of length 3 containing the cross product.

## Example

```js
o.veccross([1, 0, 0], [0, 1, 0])    // Float64Array [0, 0, 1]
o.veccross([0, 1, 0], [0, 0, 1])    // Float64Array [1, 0, 0]
```

## Notes

Memory is automatically managed via a temporary arena.

Only defined for 3D vectors.

## See Also

vecadd(3), vecdot(3), vecnorm(3)
