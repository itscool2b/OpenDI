# vecscale

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.vecscale(arr, scalar)
```

## Description

Scales every element of a vector by a scalar value.

Wraps the C `vecscale()` function.

## Parameters

- `arr`: A vector (array of numbers)
- `scalar`: The scaling factor

## Return Value

A `Float64Array` containing the scaled vector.

## Example

```js
o.vecscale([1, 2, 3], 2)      // Float64Array [2, 4, 6]
o.vecscale([10, 20], 0.5)     // Float64Array [5, 10]
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

vecadd(3), vecdot(3), matscale(3)
