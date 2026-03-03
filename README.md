# OpenDI

A lightweight, portable C library for mathematical computation and machine learning. Designed for bare-metal environments, embedded systems, and general-purpose numerical computing.

## Features

- **Primitive Operations** - Basic arithmetic (add, subtract, multiply, divide, exponents, absolute, minmax, rounding)
- **Calculus** - Numerical differentiation (forward, backward, central, second derivative) and integration (Romberg)
- **Linear Algebra** - Vectors (add, dot, cross, norm, scale) and matrices (multiply, add, scale, transpose)
- **Activations** - Neural network activation functions (relu, sigmoid, softmax)
- **Loss Functions** - Training loss computation (MSE, cross-entropy)
- **Backward Functions** - Gradient computation for activations and matrix operations
- **Optimizers** - Weight update algorithms (SGD)
- **Random** - Random number generation for weight initialization (uniform, normal, seeding)
- **Statistics** - Data preprocessing (normalize)
- **Pipeline** - Pre-built ML pipeline functions (dense layers, batch activations, loss gradients, utilities)
- **JavaScript/WASM Bindings** - `opendi-js` npm package for browsers, Node.js, Deno, and Bun
- **Zero Dependencies** - Pure C99, no external libraries required
- **Bare Metal Ready** - Works on embedded systems without OS

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
├── statistics/
│   └── normalize
│
└── pipeline/
    ├── batch_relu
    ├── batch_sigmoid
    ├── batch_softmax
    ├── batch_normalize
    ├── mse_backward
    ├── cross_entropy_backward
    ├── accuracy
    ├── init_weights
    ├── dense_forward
    └── dense_backward
```

## JavaScript / WASM

The `opendi-js` package compiles the C library to WebAssembly and wraps it with an idiomatic JS API:

```js
import { init } from 'opendi-js'
const o = await init()

o.add(1, 2, 3)                                    // 6
o.matmul([1,2,3,4], [5,6,7,8], 2, 2, 2)           // Float64Array [19,22,43,50]
o.forwarddiff(x => x * x, 3, 0.001)               // ~6.0

// Training loop with Session API
const session = o.createSession(65536)
const fwd = session.denseForward(inputPtr, weights._ptr, m, n, p, 'sigmoid')
```

See [`opendi-js/README.md`](opendi-js/README.md) for full documentation.

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
gcc -Iinclude your_program.c src/needed/files.c -o your_program -lm
```

Or include individual modules:
```c
#include "primitive/add.h"           // Just arithmetic
#include "calculus/romberg.h"        // Just integration
#include "linalg/vectors/vecadd.h"   // Just vector ops (requires arena)
#include "loss/mse_loss.h"           // Just loss functions
```

## Examples

Real-world examples are in `examples/` with documentation in `docs/examples/`:

- **`full_scenario.c`** - Physics simulation, force field analysis, statistical pipeline, and precision workflow using primitive, calculus, and vector operations
- **`cricket_pipeline.c`** - Single-layer neural network for cricket match prediction (sigmoid + MSE + SGD)
- **`mnist_pipeline.c`** - Two-layer neural network for MNIST digit classification (relu + softmax + cross-entropy + SGD)
- **`opendi-js/test/test.mjs`** - JavaScript end-to-end tests covering all WASM bindings

## Documentation

API documentation is in `docs/`. Each function has its own documentation file organized by module.

## Testing

The test suite is in `tests/`:

- **`tests/unit/`** - Unit tests for individual functions (48 test files)
- **`tests/performance/`** - Hardware-level performance benchmarks

See `tests/README.md` for detailed testing instructions.

## License

See LICENSE file for details.

---

## Transparency

This project uses AI assistance for:

- **File organization** - Test suite structure, module layout
- **Documentation** - API docs, README updates, arena allocator guide
- **Testing** - Unit tests, performance benchmarks

We believe in transparency and not slopping code.
