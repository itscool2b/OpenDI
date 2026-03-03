# randomUniform

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.randomUniform(min, max, n)
```

## Description

Generates an array of random values drawn from a uniform distribution in the range [min, max].

Call `randomSeed()` first for reproducible results.

Wraps the C `random_uniform()` function.

## Parameters

- `min`: Lower bound of the range
- `max`: Upper bound of the range
- `n`: Number of values to generate

## Return Value

A `Float64Array` of length n containing random values in [min, max].

## Example

```js
o.randomSeed(42)
const vals = o.randomUniform(0, 1, 5)
// Float64Array of 5 values, each in [0, 1]
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

randomSeed(3), randomNormal(3)
