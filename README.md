# OpenDI

A lightweight, portable C library for mathematical computation and machine learning. Designed for bare-metal environments, embedded systems, and general-purpose numerical computing.

## Features

- **Primitive Operations** - Basic arithmetic (add, subtract, multiply, divide, exponents, absolute, minmax, rounding)
- **Calculus** - Numerical differentiation (forward, backward, central) and integration (Romberg)
- **Linear Algebra** - Vectors (add, dot, cross, norm, scale) and matrices (multiply, add, scale, transpose)
- **Activations** - Neural network activation functions (relu, sigmoid, softmax)
- **Loss Functions** - Training loss computation (MSE, cross-entropy)
- **Backward Functions** - Gradient computation for activations and matrix operations
- **Optimizers** - Weight update algorithms (SGD)
- **Random** - Random number generation for weight initialization (uniform, normal, seeding)
- **Statistics** - Data preprocessing (normalize)
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
├── linalg/
│   ├── vectors/
│   │   ├── vecadd
│   │   ├── vecscale
│   │   ├── vecdot
│   │   ├── veccross
│   │   └── vecnorm
│   │
│   └── matricies/
│       ├── matadd
│       ├── matmul
│       ├── matscale
│       └── mattranspose
│
├── activations/
│   ├── relu
│   ├── sigmoid
│   └── softmax
│
├── loss/
│   ├── mse_loss
│   └── cross_entropy
│
├── backward/
│   ├── activations/
│   │   ├── relu_backward
│   │   ├── sigmoid_backward
│   │   └── softmax_backward
│   │
│   └── linalg/
│       ├── matmul_backward_a
│       └── matmul_backward_b
│
├── optimizers/
│   └── sgd_update
│
├── random/
│   ├── random_seed
│   ├── random_uniform
│   └── random_normal
│
└── statistics/
    └── normalize
```

## Quick Start

Include the master header to access all functionality:

```c
#include "opendi.h"

int main() {
    // Create an arena for memory allocation
    Arena *arena = arena_create(1024);

    // Basic arithmetic
    double sum = add_numbers(3, 1.0, 2.0, 3.0);  // Returns 6.0

    // Vector operations (using arena)
    double a[] = {1.0, 2.0, 3.0};
    double b[] = {4.0, 5.0, 6.0};
    double *result = vecadd(arena, a, b, 3);  // Returns {5.0, 7.0, 9.0}

    // Free everything at once
    arena_destroy(arena);
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
#include "linalg/vectors/vecadd.h"   // Just vector ops (requires arena)
#include "loss/mse_loss.h"           // Just loss functions
```

## License

See LICENSE file for details.

---

## Transparency

This project uses AI assistance for:

- **File organization** - Test suite structure (unit/scenarios/performance)
- **Documentation** - API docs, README updates, arena allocator guide
- **Testing** - Unit tests, scenario tests, performance benchmarks

We believe in transparency and not slopping code.
