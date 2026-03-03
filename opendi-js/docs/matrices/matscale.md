# matscale

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.matscale(a, scalar, m, n)
```

## Description

Scales every element of a matrix by a scalar value.

Wraps the C `matscale()` function.

## Parameters

- `a`: Matrix as a flat array (m * n elements, row-major)
- `scalar`: The scaling factor
- `m`: Number of rows
- `n`: Number of columns

## Return Value

A `Float64Array` of length m * n containing the scaled matrix.

## Example

```js
o.matscale([1,2,3,4], 3, 2, 2)
// Float64Array [3, 6, 9, 12]
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

matmul(3), matadd(3), mattranspose(3), vecscale(3)
