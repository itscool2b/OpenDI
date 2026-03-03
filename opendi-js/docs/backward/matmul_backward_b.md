# matmulBackwardB

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.matmulBackwardB(a, dout, m, n, p)
```

## Description

Computes the gradient of matrix multiplication with respect to the second matrix B.

Given `C = A @ B` where A is m x n and B is n x p, computes `dB = A^T @ dout`.

Wraps the C `matmul_backward_b()` function.

## Parameters

- `a`: The A matrix from the forward pass (flat array, m * n elements)
- `dout`: Upstream gradient (flat array, m * p elements)
- `m`: Number of rows in A
- `n`: Number of columns in A (and rows in B)
- `p`: Number of columns in B

## Return Value

A `Float64Array` of length n * p containing the gradient with respect to B.

## Example

```js
const dB = o.matmulBackwardB(a, dout, 2, 3, 1)
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

matmulBackwardA(3), matmul(3), denseBackward(3)
