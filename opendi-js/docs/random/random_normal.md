# randomNormal

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.randomNormal(mean, std, n)
```

## Description

Generates an array of random values drawn from a normal (Gaussian) distribution with the specified mean and standard deviation.

Call `randomSeed()` first for reproducible results.

Wraps the C `random_normal()` function.

## Parameters

- `mean`: Mean of the distribution
- `std`: Standard deviation of the distribution
- `n`: Number of values to generate

## Return Value

A `Float64Array` of length n containing normally distributed values.

## Example

```js
o.randomSeed(42)
const vals = o.randomNormal(0, 1, 5)
// Float64Array of 5 values ~ N(0, 1)
```

## Notes

Memory is automatically managed via a temporary arena.

## See Also

randomSeed(3), randomUniform(3), initWeights(3)
