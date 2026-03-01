# random_seed

## Synopsis

```c
#include "random/random_seed.h"

void random_seed(unsigned int seed);
```

## Description

Sets the seed for the random number generator.

Wraps the standard `srand()` function to provide reproducible random sequences. Setting the same seed before calling `random_uniform` or `random_normal` will produce identical results.

## Parameters

- `seed`: The seed value for the random number generator

## Return Value

None.

## Example

```c
random_seed(42);
// All subsequent random_uniform/random_normal calls will produce
// the same sequence every time seed 42 is used
```

## Notes

Call this before any random functions to ensure reproducibility.

Setting seed to 0 is valid and will produce a deterministic sequence.

## See Also

random_uniform(3), random_normal(3)
