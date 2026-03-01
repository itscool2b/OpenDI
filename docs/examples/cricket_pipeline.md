# cricket_pipeline

## Synopsis

```c
gcc -Iinclude examples/cricket_pipeline.c \
  src/statistics/normalize.c \
  src/random/random_seed.c src/random/random_normal.c \
  src/linalg/matricies/matmul.c src/linalg/matricies/mattranspose.c \
  src/activations/sigmoid.c src/primitive/exponents/exponents.c \
  src/loss/mse_loss.c \
  src/backward/activations/sigmoid_backward.c \
  src/backward/linalg/matmul_backward_b.c \
  src/optimizers/sgd_update.c \
  -o cricket_pipeline -lm
```

## Description

Trains a single-layer neural network (logistic regression) to predict cricket match outcomes from player performance statistics.

The pipeline reads `pak_vs_ind_cricket_dataset.csv` containing 20 player entries with 8 numeric features each. It classifies each entry as Win or Lose using a sigmoid output and MSE loss, trained with SGD.

The training process:
```
1. Parse CSV into feature matrix X (20x8) and target vector y (20x1)
2. Normalize each feature column with normalize()
3. Initialize weight vector W (8x1) with random_normal()
4. For each epoch:
   z    = matmul(X, W)                    (20x8 @ 8x1 = 20x1)
   pred = sigmoid(z)                      (element-wise)
   loss = mse_loss(pred, targets)
   grad = sigmoid_backward * matmul_backward_b
   W    = sgd_update(W, grad, lr)
5. Evaluate predictions against actual results
```

## Dataset

The CSV file `pak_vs_ind_cricket_dataset.csv` must be in the working directory.

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

- `normalize()`: Z-score normalization of each feature column
- `random_seed()`: Seed the RNG for reproducible weight initialization
- `random_normal()`: Initialize weights from a Gaussian distribution
- `matmul()`: Forward pass matrix multiplication (X @ W)
- `sigmoid()`: Activation function applied element-wise
- `mse_loss()`: Mean squared error between predictions and targets
- `sigmoid_backward()`: Gradient of sigmoid for backpropagation
- `matmul_backward_b()`: Gradient of matmul with respect to weights (X^T @ d_sig)
- `sgd_update()`: Weight update (W = W - lr * grad)
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

The arena is cleared after each epoch to reuse memory for temporary allocations. Weights are copied to a stack array before clearing.

All 10 Pakistan entries are labeled Win and all 10 India entries are labeled Lose. The model achieves 90% accuracy, misclassifying 2 India players whose stats resemble winning patterns.

Increasing epochs or tuning the learning rate may improve convergence but will not change accuracy on this dataset due to inherent overlap in the feature space.

## See Also

normalize(3), random_seed(3), random_normal(3), matmul(3), sigmoid(3), mse_loss(3), sigmoid_backward(3), matmul_backward_b(3), sgd_update(3)
