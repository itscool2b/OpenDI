# matmulBackwardA

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.matmulBackwardA(dout, b, m, n, p)
```

## Description

Computes the gradient of matrix multiplication with respect to the first matrix A.

Given `C = A @ B` where A is m x n and B is n x p, computes `dA = dout @ B^T`.

Wraps the C `matmul_backward_a()` function.

## Parameters

- `dout`: Upstream gradient (flat array, m * p elements)
- `b`: The B matrix from the forward pass (flat array, n * p elements)
- `m`: Number of rows in A
- `n`: Number of columns in A (and rows in B)
- `p`: Number of columns in B

## Return Value

A `Float64Array` of length m * n containing the gradient with respect to A.

## Example

```js
const dA = o.matmulBackwardA(dout, b, 2, 3, 1)
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

matmulBackwardB(3), matmul(3), denseBackward(3)
