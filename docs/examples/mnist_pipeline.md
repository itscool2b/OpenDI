# mnist_pipeline

## Synopsis

```c
gcc -Iinclude examples/mnist_pipeline.c \
  src/linalg/matricies/matmul.c src/linalg/matricies/mattranspose.c \
  src/activations/relu.c src/activations/sigmoid.c \
  src/primitive/exponents/exponents.c \
  src/loss/cross_entropy.c \
  src/backward/activations/relu_backward.c \
  src/backward/activations/sigmoid_backward.c \
  src/backward/linalg/matmul_backward_a.c \
  src/backward/linalg/matmul_backward_b.c \
  src/optimizers/sgd_update.c \
  src/random/random_seed.c src/random/random_normal.c \
  src/pipeline/init_weights.c \
  src/pipeline/accuracy.c \
  src/pipeline/cross_entropy_backward.c \
  src/pipeline/dense_forward.c \
  src/pipeline/dense_backward.c \
  -o mnist_pipeline -lm
```

## Description

Trains a two-layer neural network to classify handwritten digits (0-9) from the MNIST dataset using softmax output and cross-entropy loss, trained with SGD.

The pipeline reads IDX binary files containing 28x28 grayscale images. It uses 1000 training images and 500 test images. Pixel values are normalized to [0, 1] by dividing by 255. Labels are one-hot encoded for training.

The training process:
```
1. Read IDX binary files into image/label arrays
2. Normalize pixel values to [0, 1]
3. One-hot encode training labels (10 classes)
4. Initialize W1 (784x128) and W2 (128x10) with init_weights()
5. For each epoch:
   h    = dense_forward(X, W1, ACTIVATION_RELU)
   pred = dense_forward(h, W2, ACTIVATION_SOFTMAX)
   loss = cross_entropy(pred, targets)
   d_z2 = cross_entropy_backward(pred, targets)
   grad2 = dense_backward(d_z2, h, W2, ACTIVATION_NONE)
   grad1 = dense_backward(grad2.d_input, X, W1, ACTIVATION_RELU)
   W1 = sgd_update(W1, grad1.d_weights, lr)
   W2 = sgd_update(W2, grad2.d_weights, lr)
6. Evaluate predictions on test set with accuracy()
```

## Dataset

The MNIST IDX binary files must be in `datasets/mnist_data/` in the working directory:

- `train-images.idx3-ubyte`: 60000 training images (first 1000 used)
- `train-labels.idx1-ubyte`: 60000 training labels (first 1000 used)
- `t10k-images.idx3-ubyte`: 10000 test images (first 500 used)
- `t10k-labels.idx1-ubyte`: 10000 test labels (first 500 used)

Each image is 28x28 pixels (784 values), stored as unsigned bytes. The IDX image files have a 16-byte header and label files have an 8-byte header.

## Configuration

- `N_TRAIN`: 1000 (number of training images)
- `N_TEST`: 500 (number of test images)
- `N_PIXELS`: 784 (28x28 pixels per image)
- `N_HIDDEN`: 128 (hidden layer neurons)
- `N_CLASSES`: 10 (digits 0-9)
- `EPOCHS`: 200 (training iterations)
- `LR`: 1.0 (learning rate for SGD)

## OpenDI Functions Used

- `random_seed()`: Seed the RNG for reproducible weight initialization
- `init_weights()`: Initialize weights from a Gaussian distribution (malloc'd)
- `dense_forward()`: Forward pass: matmul + activation (RELU for hidden, SOFTMAX for output)
- `cross_entropy()`: Cross-entropy loss between predictions and one-hot targets
- `cross_entropy_backward()`: Combined softmax + cross-entropy gradient
- `dense_backward()`: Backward pass: activation_backward + matmul gradients
- `sgd_update()`: Weight update (W = W - lr * grad)
- `accuracy()`: Compute multiclass classification accuracy (argmax)
- `arena_create()`, `arena_clear()`, `arena_destroy()`: Memory management

## Example

```
$ ./mnist_pipeline
=== Training ===

Epoch   0  loss: 0.2426  acc: 9.1%
Epoch   5  loss: 0.1181  acc: 65.9%
Epoch  10  loss: 0.0934  acc: 70.5%
Epoch  15  loss: 0.0432  acc: 88.0%
Epoch  20  loss: 0.0332  acc: 91.0%
...
Epoch  95  loss: 0.0035  acc: 100.0%
...
Epoch 195  loss: 0.0011  acc: 100.0%

=== Predictions ===

Sample  1  pred: 7  actual: 7  [PASS]
Sample  2  pred: 2  actual: 2  [PASS]
Sample  3  pred: 1  actual: 1  [PASS]
...
Sample  9  pred: 2  actual: 5  [FAIL]
...
Sample 20  pred: 4  actual: 4  [PASS]

=== Results ===
Test Accuracy: 437/500 (87.4%)
```

## Notes

The arena is cleared after each epoch to reuse memory for temporary allocations. Weights are heap-allocated via `init_weights()` and survive arena clears.

Weight initialization uses He-style standard deviations: 0.05 for W1 (approximating sqrt(2/784)) and 0.1 for W2 (approximating sqrt(2/128)). This ensures activations maintain reasonable scale through the network.

The softmax + cross-entropy gradient is computed with `cross_entropy_backward()`, which returns `(pred - target) / N`. This is paired with `ACTIVATION_NONE` in `dense_backward()` since the activation gradient is already incorporated.

The model achieves 100% training accuracy by epoch 95 and 87.4% test accuracy on 500 unseen images. The gap indicates overfitting, expected with 100K+ parameters and only 1000 training samples. Increasing `N_TRAIN` would improve generalization.

## See Also

init_weights(3), dense_forward(3), dense_backward(3), cross_entropy(3), cross_entropy_backward(3), accuracy(3), sgd_update(3)
