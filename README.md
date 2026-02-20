# OpenDI

A lightweight, portable C library for mathematical computation. Designed for bare-metal environments, embedded systems, and general-purpose numerical computing.

## Features

- **Primitive Operations** - Basic arithmetic (add, subtract, multiply, divide, exponents, absolute, minmax, rounding)
- **Calculus** - Numerical differentiation (forward, backward, central) and integration (Romberg)
- **Linear Algebra** - Vector operations (addition, dot product, cross product, norm, scaling)
- **Zero Dependencies** - Pure C99, no external libraries required
- **Bare Metal Ready** - Works on embedded systems without OS

## Documentation

API documentation is located in `docs/`. Each function has its own documentation file organized by module.

## Testing

The test suite is organized into three categories:

- **`tests/unit/`** - Unit tests for individual functions
- **`tests/scenarios/`** - Real-world scenario tests (functions working together)
- **`tests/performance/`** - Hardware-level performance benchmarks

See `tests/README.md` for detailed testing instructions.

## Current Modules

```
src/
├── primitive/
│   ├── absolute
│   ├── add
│   ├── subtract
│   ├── multiply
│   ├── divide
│   ├── minmax
│   ├── rounding
│   └── exponents
│
├── calculus/
│   ├── derivatives/
│   │   ├── forwarddiff
│   │   ├── backwarddiff
│   │   ├── centraldiff
│   │   └── secondderivative
│   │
│   └── integrals/
│       └── romberg
│
└── linalg/
    └── vectors/
        ├── vecadd
        ├── vecscale
        ├── vecdot
        ├── veccross
        └── vecnorm
```

## Quick Start

Include the master header to access all functionality:

```c
#include "opendi.h"
#include <stdlib.h>  // For free()

int main() {
    // Basic arithmetic
    double sum = add_numbers(3, 1.0, 2.0, 3.0);  // Returns 6.0
    
    // Vector operations
    double a[] = {1.0, 2.0, 3.0};
    double b[] = {4.0, 5.0, 6.0};
    double *result = vecadd(a, b, 3);  // Returns {5.0, 7.0, 9.0}
    
    free(result);  // Remember to free allocated memory
    return 0;
}
```

Compile with:
```bash
gcc -I/path/to/opendi/include your_program.c -o your_program -lm
```

Or include individual modules:
```c
#include "primitive/add.h"           // Just arithmetic
#include "calculus/romberg.h"        // Just integration
#include "linalg/vectors/vecadd.h"   // Just vector ops
```

## License

See LICENSE file for details.
