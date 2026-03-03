# vecnorm

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.vecnorm(arr)
```

## Description

Computes the Euclidean norm (L2 norm) of a vector.

The norm is defined as `sqrt(sum(x[i]^2))`.

Wraps the C `vecnorm()` function.

## Parameters

- `arr`: A vector (array of numbers)

## Return Value

The Euclidean norm as a `number`.

## Example

```js
o.vecnorm([3, 4])          // 5
o.vecnorm([1, 0, 0])       // 1
o.vecnorm([1, 1, 1, 1])    // 2
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

vecadd(3), vecdot(3), veccross(3)
