# matmul

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.matmul(a, b, m, n, p)
```

## Description

Computes the matrix product of two matrices. Matrix A is m x n and matrix B is n x p, producing an m x p result.

Matrices are represented as flat arrays in row-major order.

Wraps the C `matmul()` function.

## Parameters

- `a`: First matrix as a flat array (m * n elements, row-major)
- `b`: Second matrix as a flat array (n * p elements, row-major)
- `m`: Number of rows in A
- `n`: Number of columns in A (and rows in B)
- `p`: Number of columns in B

## Return Value

A `Float64Array` of length m * p containing the matrix product in row-major order.

## Example

```js
// [1 2] x [5 6] = [19 22]
// [3 4]   [7 8]   [43 50]
o.matmul([1,2,3,4], [5,6,7,8], 2, 2, 2)
// Float64Array [19, 22, 43, 50]

// Vector-matrix multiply (1x3 x 3x1 = 1x1)
o.matmul([1,2,3], [4,5,6], 1, 3, 1)
// Float64Array [32]
```

## Notes

Memory is automatically managed via a temporary arena.

For training loops, use `session.matmul()` with WASM pointers for better performance.

## See Also

matadd(3), matscale(3), mattranspose(3), matmulBackwardA(3), matmulBackwardB(3)
