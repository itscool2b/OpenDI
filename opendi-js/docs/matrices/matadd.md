# matadd

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.matadd(a, b, m, n)
```

## Description

Computes the element-wise sum of two matrices of the same dimensions.

Wraps the C `matadd()` function.

## Parameters

- `a`: First matrix as a flat array (m * n elements, row-major)
- `b`: Second matrix as a flat array (m * n elements, row-major)
- `m`: Number of rows
- `n`: Number of columns

## Return Value

A `Float64Array` of length m * n containing the element-wise sum.

## Example

```js
o.matadd([1,2,3,4], [10,20,30,40], 2, 2)
// Float64Array [11, 22, 33, 44]
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

matmul(3), matscale(3), mattranspose(3), vecadd(3)
