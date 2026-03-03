# mattranspose

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.mattranspose(a, m, n)
```

## Description

Computes the transpose of a matrix. An m x n matrix becomes n x m.

Wraps the C `mattranspose()` function.

## Parameters

- `a`: Matrix as a flat array (m * n elements, row-major)
- `m`: Number of rows
- `n`: Number of columns

## Return Value

A `Float64Array` of length n * m containing the transposed matrix in row-major order.

## Example

```js
// [1 2 3]T = [1 4]
// [4 5 6]    [2 5]
//            [3 6]
o.mattranspose([1,2,3,4,5,6], 2, 3)
// Float64Array [1, 4, 2, 5, 3, 6]
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

matmul(3), matadd(3), matscale(3)
