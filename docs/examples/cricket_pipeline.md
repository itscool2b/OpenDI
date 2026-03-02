# cricket_pipeline

## Synopsis

```c
gcc -Iinclude examples/cricket_pipeline.c \
  src/statistics/normalize.c \
  src/random/random_seed.c src/random/random_normal.c \
  src/linalg/matricies/matmul.c src/linalg/matricies/mattranspose.c \
  src/activations/sigmoid.c src/activations/relu.c \
  src/primitive/exponents/exponents.c \
  src/loss/mse_loss.c \
  src/backward/activations/sigmoid_backward.c \
  src/backward/activations/relu_backward.c \
  src/backward/linalg/matmul_backward_a.c \
  src/backward/linalg/matmul_backward_b.c \
  src/optimizers/sgd_update.c \
  src/pipeline/batch_normalize.c \
  src/pipeline/mse_backward.c \
  src/pipeline/accuracy.c \
  src/pipeline/init_weights.c \
  src/pipeline/dense_forward.c \
  src/pipeline/dense_backward.c \
  -o cricket_pipeline -lm
```

## Description

Trains a single-layer neural network (logistic regression) to predict cricket match outcomes from player performance statistics.

The pipeline reads `datasets/pak_vs_ind_cricket_dataset.csv` containing 20 player entries with 8 numeric features each. It classifies each entry as Win or Lose using a sigmoid output and MSE loss, trained with SGD.

The training process:
```
1. Parse CSV into feature matrix X (20x8) and target vector y (20x1)
2. Normalize all feature columns with batch_normalize()
3. Initialize weight vector W (8x1) with init_weights()
4. For each epoch:
   pred = dense_forward(X, W, ACTIVATION_SIGMOID)
   loss = mse_loss(pred, targets)
   grad = mse_backward + dense_backward(ACTIVATION_SIGMOID)
   W    = sgd_update(W, grad.d_weights, lr)
5. Evaluate predictions with accuracy()
```

## Dataset

The CSV file `datasets/pak_vs_ind_cricket_dataset.csv` must be in the `datasets/` directory relative to the working directory.

Features used (columns 4-11):
- `runs_scored`: Total runs scored by the player
- `balls_faced`: Number of balls faced
- `fours`: Number of boundary fours hit
- `sixes`: Number of sixes hit
- `wickets_taken`: Number of wickets taken
- `overs_bowled`: Number of overs bowled
- `economy_rate`: Runs conceded per over
- `strike_rate`: Runs scored per 100 balls

Target (column 12):
- `match_result`: Win (1.0) or Lose (0.0)

## Configuration

- `N_SAMPLES`: 20 (number of rows in the dataset)
- `N_FEATURES`: 8 (number of numeric input features)
- `EPOCHS`: 5000 (training iterations)
- `LR`: 0.5 (learning rate for SGD)

## OpenDI Functions Used

- `batch_normalize()`: Z-score normalization of all feature columns at once
- `random_seed()`: Seed the RNG for reproducible weight initialization
- `init_weights()`: Initialize weights from a Gaussian distribution (malloc'd)
- `dense_forward()`: Forward pass: matmul + sigmoid activation
- `mse_loss()`: Mean squared error between predictions and targets
- `mse_backward()`: MSE gradient computation
- `dense_backward()`: Backward pass: sigmoid_backward + matmul gradients
- `sgd_update()`: Weight update (W = W - lr * grad)
- `accuracy()`: Compute classification accuracy with threshold 0.5
- `arena_create()`, `arena_clear()`, `arena_destroy()`: Memory management

## Example

```
$ ./cricket_pipeline
=== Training ===

Epoch    0  loss: 0.276368
Epoch  500  loss: 0.081486
Epoch 1000  loss: 0.078093
Epoch 1500  loss: 0.076431
...
Epoch 4500  loss: 0.073042

=== Predictions ===

Sample  1  pred: 0.6107  class: Win   actual: Win   [PASS]
Sample  2  pred: 0.9457  class: Win   actual: Win   [PASS]
...
Sample 20  pred: 0.5665  class: Win   actual: Lose  [FAIL]

=== Results ===
Accuracy: 18/20 (90.0%)
Final loss: 0.072782
```

## Notes

The arena is cleared after each epoch to reuse memory for temporary allocations. Weights are heap-allocated via `init_weights()` and survive arena clears.

All 10 Pakistan entries are labeled Win and all 10 India entries are labeled Lose. The model achieves 90% accuracy, misclassifying 2 India players whose stats resemble winning patterns.

Increasing epochs or tuning the learning rate may improve convergence but will not change accuracy on this dataset due to inherent overlap in the feature space.

## See Also

batch_normalize(3), init_weights(3), dense_forward(3), dense_backward(3), mse_loss(3), mse_backward(3), accuracy(3), sgd_update(3)
