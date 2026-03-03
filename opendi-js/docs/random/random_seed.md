# randomSeed

## Synopsis

```js
import { init } from 'opendi-js'
const o = await init()

o.randomSeed(seed)
```

## Description

Seeds the random number generator for reproducible results.

Must be called before `randomUniform()`, `randomNormal()`, or `initWeights()` to get deterministic output.

Wraps the C `random_seed()` function directly.

## Parameters

- `seed`: An integer seed value

## Return Value

None.

## Example

```js
o.randomSeed(42)
const a = o.randomUniform(0, 1, 3)

o.randomSeed(42)
const b = o.randomUniform(0, 1, 3)
// a and b are identical
```

## Notes

No arena allocation needed. Calls the WASM function directly.

## See Also

randomUniform(3), randomNormal(3), initWeights(3)
