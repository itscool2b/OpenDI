# ML Functions Roadmap

Functions to add for machine learning support.

## Priority 1: Core (Start Here)

### Matrix Operations
| Function | Signature | Purpose |
|----------|-----------|---------|
| matmul | `double *matmul(Arena*, double *A, double *B, int m, int n, int p)` | Matrix multiplication |
| mattranspose | `double *mattranspose(Arena*, double *A, int m, int n)` | Transpose matrix |
| matadd | `double *matadd(Arena*, double *A, double *B, int m, int n)` | Element-wise add |
| matscale | `double *matscale(Arena*, double *A, double s, int m, int n)` | Scalar multiply |

### Activations
| Function | Signature | Purpose |
|----------|-----------|---------|
| relu | `double relu(double x)` | max(0, x) |
| sigmoid | `double sigmoid(double x)` | 1/(1+e^-x) |
| tanh_act | `double tanh_act(double x)` | Hyperbolic tangent |
| softmax | `double *softmax(Arena*, double *v, int n)` | exp(xi)/sum(exp(x)) |

### Random
| Function | Signature | Purpose |
|----------|-----------|---------|
| random_uniform | `double random_uniform(double min, double max)` | Uniform distribution |
| random_normal | `double random_normal(double mean, double std)` | Gaussian distribution |
| random_xavier | `double random_xavier(int n_in, int n_out)` | Xavier/Glorot init |

---

## Priority 2: Essential

### Loss Functions
| Function | Signature | Purpose |
|----------|-----------|---------|
| mse_loss | `double mse_loss(double *y_t, double *y_p, int n)` | Mean squared error |
| mae_loss | `double mae_loss(double *y_t, double *y_p, int n)` | Mean absolute error |
| cross_entropy | `double cross_entropy(double *y_t, double *y_p, int n)` | Cross-entropy loss |

### Statistics
| Function | Signature | Purpose |
|----------|-----------|---------|
| mean | `double mean(double *v, int n)` | Arithmetic mean |
| variance | `double variance(double *v, int n)` | Population variance |
| stddev | `double stddev(double *v, int n)` | Standard deviation |
| zscore_normalize | `double *zscore_normalize(Arena*, double *v, int n)` | (x - mean) / std |
| minmax_scale | `double *minmax_scale(Arena*, double *v, int n, double mn, double mx)` | Scale to range |

### Elementary
| Function | Signature | Purpose |
|----------|-----------|---------|
| exp_func | `double exp_func(double x)` | e^x (avoid math.h conflict) |
| log_func | `double log_func(double x)` | Natural log |
| pow_func | `double pow_func(double b, double e)` | b^e |

---

## Priority 3: Useful

### Vector Reductions
| Function | Signature | Purpose |
|----------|-----------|---------|
| vecsum | `double vecsum(double *v, int n)` | Sum of elements |
| vecmax | `double vecmax(double *v, int n)` | Maximum value |
| vecmin | `double vecmin(double *v, int n)` | Minimum value |
| argmax | `int argmax(double *v, int n)` | Index of max |
| argmin | `int argmin(double *v, int n)` | Index of min |
| vecclip | `void vecclip(double *v, int n, double mn, double mx)` | Clip values |

### More Activations
| Function | Signature | Purpose |
|----------|-----------|---------|
| leaky_relu | `double leaky_relu(double x, double a)` | max(ax, x) |
| elu | `double elu(double x, double a)` | Exponential LU |
| swish | `double swish(double x)` | x * sigmoid(x) |

### Distance Metrics
| Function | Signature | Purpose |
|----------|-----------|---------|
| euclidean_dist | `double euclidean_dist(double *a, double *b, int n)` | L2 distance |
| manhattan_dist | `double manhattan_dist(double *a, double *b, int n)` | L1 distance |
| cosine_sim | `double cosine_sim(double *a, double *b, int n)` | Cosine similarity |

---

## Priority 4: Advanced

### Matrix Decomposition
| Function | Signature | Purpose |
|----------|-----------|---------|
| matinverse | `double *matinverse(Arena*, double *A, int n)` | Matrix inverse |
| matdet | `double matdet(double *A, int n)` | Determinant |
| matsolve | `double *matsolve(Arena*, double *A, double *b, int n)` | Solve Ax = b |

### Convolution
| Function | Signature | Purpose |
|----------|-----------|---------|
| conv1d | `double *conv1d(Arena*, double *in, double *k, int n, int kn)` | 1D convolution |
| maxpool1d | `double *maxpool1d(Arena*, double *in, int n, int p)` | Max pooling |
| avgpool1d | `double *avgpool1d(Arena*, double *in, int n, int p)` | Average pooling |

### Random (More)
| Function | Signature | Purpose |
|----------|-----------|---------|
| random_he | `double random_he(int n_in)` | He initialization |
| random_shuffle | `void random_shuffle(int *a, int n)` | Shuffle array |
| random_seed | `void random_seed(unsigned int s)` | Set seed |

---

## Folder Structure

```
include/
├── linalg/
│   ├── mat/           # Matrix operations
│   │   ├── matmul.h
│   │   ├── mattranspose.h
│   │   └── ...
│   └── distance/      # Distance metrics
│       └── ...
├── ml/
│   ├── activations/   # Activation functions
│   ├── loss/          # Loss functions
│   └── conv/          # Convolution ops
├── stats/             # Statistics
└── utils/
    └── random/        # Random numbers
```
