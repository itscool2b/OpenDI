# ML Functions Roadmap

This roadmap focuses on the **minimum required functions** to make OpenDI a working ML library that can actually train neural networks.

---

## ✅ COMPLETED

### Matrix Operations
| Function | Status | Purpose |
|----------|--------|---------|
| matmul | ✅ DONE | Matrix multiplication |
| mattranspose | ✅ DONE | Transpose matrix |
| matadd | ✅ DONE | Element-wise add |
| matscale | ✅ DONE | Scalar multiply |

### Activations (Forward Pass)
| Function | Status | Purpose |
|----------|--------|---------|
| relu | ✅ DONE | max(0, x) |
| sigmoid | ✅ DONE | 1/(1+e^-x) |
| softmax | ✅ DONE | exp(xi)/sum(exp(x)) |

---

## 🎯 PRIORITY 0: Minimum Viable ML (7 functions)

**These 7 functions are REQUIRED to train any neural network.**

### Loss Functions (1/7)
| Function | Signature | Purpose |
|----------|-----------|---------|
| mse_loss | `double mse_loss(double *predictions, double *targets, int n)` | Mean squared error - universal loss |

### Backward/Gradient Functions (4/7)
| Function | Signature | Purpose |
|----------|-----------|---------|
| relu_backward | `double *relu_backward(Arena*, double *dout, double *input, int n)` | Gradient through ReLU |
| sigmoid_backward | `double *sigmoid_backward(Arena*, double *dout, double *output, int n)` | Gradient through sigmoid |
| matmul_backward_a | `double *matmul_backward_a(Arena*, double *dout, double *b, int m, int n, int p)` | Gradient for first matrix (dout @ B^T) |
| matmul_backward_b | `double *matmul_backward_b(Arena*, double *a, double *dout, int m, int n, int p)` | Gradient for second matrix (A^T @ dout) |

### Optimizer (1/7)
| Function | Signature | Purpose |
|----------|-----------|---------|
| sgd_update | `double *sgd_update(Arena*, double *weights, double *grads, double lr, int n)` | Weight update: w = w - lr * grad |

### Random Initialization (1/7)
| Function | Signature | Purpose |
|----------|-----------|---------|
| random_uniform | `double *random_uniform(Arena*, double min, double max, int n)` | Uniform random in [min, max] |

**With these 7 functions, you can train a working neural network.**

---

## 🔥 PRIORITY 1: Essential Extras (5 functions)

**These make training significantly better but aren't strictly required.**

### Better Loss (1/5)
| Function | Signature | Purpose |
|----------|-----------|---------|
| cross_entropy | `double cross_entropy(double *predictions, double *targets, int n)` | Better for classification |

### Better Initialization (1/5)
| Function | Signature | Purpose |
|----------|-----------|---------|
| random_normal | `double *random_normal(Arena*, double mean, double std, int n)` | Gaussian distribution (better than uniform) |

### Reproducibility (1/5)
| Function | Signature | Purpose |
|----------|-----------|---------|
| random_seed | `void random_seed(unsigned int seed)` | Set seed for reproducible results |

### Data Preprocessing (2/5)
| Function | Signature | Purpose |
|----------|-----------|---------|
| normalize | `double *normalize(Arena*, double *v, int n)` | Z-score: (x - mean) / std |
| softmax_backward | `double *softmax_backward(Arena*, double *dout, double *output, int n)` | Gradient through softmax |

---

## 💎 PRIORITY 2: Nice to Have

### More Statistics
| Function | Signature | Purpose |
|----------|-----------|---------|
| mean | `double mean(double *v, int n)` | Arithmetic mean |
| variance | `double variance(double *v, int n)` | Population variance |
| stddev | `double stddev(double *v, int n)` | Standard deviation |
| minmax_scale | `double *minmax_scale(Arena*, double *v, int n, double mn, double mx)` | Scale to range |

### Better Optimizers
| Function | Signature | Purpose |
|----------|-----------|---------|
| adam_update | `double *adam_update(Arena*, double *w, double *g, double lr, ...)` | Adam optimizer (faster convergence) |

### Vector Reductions
| Function | Signature | Purpose |
|----------|-----------|---------|
| vecsum | `double vecsum(double *v, int n)` | Sum of elements |
| vecmax | `double vecmax(double *v, int n)` | Maximum value |
| vecmin | `double vecmin(double *v, int n)` | Minimum value |
| argmax | `int argmax(double *v, int n)` | Index of max |
| argmin | `int argmin(double *v, int n)` | Index of min |

---

## 🚀 PRIORITY 3: Advanced (Future)

### Vector Reductions
| Function | Signature | Purpose |
|----------|-----------|---------|
| vecsum | `double vecsum(double *v, int n)` | Sum of elements |
| vecmax | `double vecmax(double *v, int n)` | Maximum value |
| vecmin | `double vecmin(double *v, int n)` | Minimum value |
| argmax | `int argmax(double *v, int n)` | Index of max |
| argmin | `int argmin(double *v, int n)` | Index of min |

### More Activations
| Function | Signature | Purpose |
|----------|-----------|---------|
| leaky_relu | `double leaky_relu(double x, double a)` | max(ax, x) |
| elu | `double elu(double x, double a)` | Exponential LU |
| swish | `double swish(double x)` | x * sigmoid(x) |

### Matrix Decomposition
| Function | Signature | Purpose |
|----------|-----------|---------|
| matinverse | `double *matinverse(Arena*, double *A, int n)` | Matrix inverse |
| matdet | `double matdet(double *A, int n)` | Determinant |

### Convolution (for CNNs)
| Function | Signature | Purpose |
|----------|-----------|---------|
| conv1d | `double *conv1d(Arena*, double *in, double *k, int n, int kn)` | 1D convolution |
| maxpool1d | `double *maxpool1d(Arena*, double *in, int n, int p)` | Max pooling |

---

## 📊 SUMMARY

**To make OpenDI a functional ML library:**
- **Minimum (7 functions)**: Loss, backward passes, SGD, random init → Can train
- **Extras (5 functions)**: Better loss, preprocessing, reproducibility → Train well
- **Total: 12 functions needed**

Everything else is optimization or advanced features for later.

---

## 📁 Folder Structure

```
include/
├── loss/              # Loss functions (mse, cross_entropy)
├── backward/          # Gradient functions
│   ├── activations/   # relu_backward, sigmoid_backward, softmax_backward
│   └── linalg/        # matmul_backward_a, matmul_backward_b
├── optimizers/        # sgd_update, adam_update
├── random/            # random_uniform, random_normal, random_seed
├── statistics/        # mean, stddev, normalize
├── activations/       # ✅ DONE (relu, sigmoid, softmax)
└── linalg/
    ├── vectors/       # ✅ DONE
    └── matricies/     # ✅ DONE
```
