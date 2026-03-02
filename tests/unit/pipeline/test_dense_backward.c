#include <stdio.h>
#include <math.h>
#include "../../../include/pipeline/dense_forward.h"
#include "../../../include/pipeline/dense_backward.h"
#include "../../../include/arena.h"

#define EPSILON 1e-4

int test_passed = 0;
int test_failed = 0;

void check(int condition, const char *test_name) {
    if (condition) {
        printf("[PASS] %s\n", test_name);
        test_passed++;
    } else {
        printf("[FAIL] %s\n", test_name);
        test_failed++;
    }
}

int main() {
    printf("=== Testing dense_backward ===\n\n");

    Arena *arena = arena_create(65536);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: ACTIVATION_NONE - gradient passes straight through
    // input (2x2), weights (2x1), dout (2x1)
    double input1[] = {1.0, 2.0, 3.0, 4.0};
    double weights1[] = {0.5, 0.5};
    double dout1[] = {1.0, 1.0};

    LayerGrad grad = dense_backward(arena, dout1, input1, weights1, NULL, 2, 2, 1, ACTIVATION_NONE);
    check(grad.d_weights != NULL, "ACTIVATION_NONE: d_weights non-null");
    check(grad.d_input != NULL, "ACTIVATION_NONE: d_input non-null");

    // d_weights = input^T @ dout = [[1,3],[2,4]]^T @ [[1],[1]] = [4, 6]
    check(fabs(grad.d_weights[0] - 4.0) < EPSILON &&
          fabs(grad.d_weights[1] - 6.0) < EPSILON,
          "ACTIVATION_NONE: d_weights correct");

    // d_input = dout @ weights^T = [[1],[1]] @ [[0.5, 0.5]] = [[0.5, 0.5],[0.5, 0.5]]
    check(fabs(grad.d_input[0] - 0.5) < EPSILON &&
          fabs(grad.d_input[1] - 0.5) < EPSILON &&
          fabs(grad.d_input[2] - 0.5) < EPSILON &&
          fabs(grad.d_input[3] - 0.5) < EPSILON,
          "ACTIVATION_NONE: d_input correct");

    arena_clear(arena);

    // Test 2: ACTIVATION_RELU - gradient zeroed where z <= 0
    double input2[] = {1.0, -1.0};
    double weights2[] = {1.0};
    // z = matmul([1,-1], [1]) = [1, -1]
    // relu(z) = [1, 0]
    // cache = z = [1, -1]
    double *cache2;
    dense_forward(arena, input2, weights2, 2, 1, 1, ACTIVATION_RELU, &cache2);

    double dout2[] = {1.0, 1.0};
    grad = dense_backward(arena, dout2, input2, weights2, cache2, 2, 1, 1, ACTIVATION_RELU);

    // relu_backward: [1*(1>0)=1, 1*(-1>0)=0] = [1, 0]
    // d_weights = input^T @ d_act = [1, -1]^T @ [1, 0] = [1*1 + (-1)*0] = [1]
    check(fabs(grad.d_weights[0] - 1.0) < EPSILON,
          "ACTIVATION_RELU: d_weights zeroes blocked gradient");

    arena_clear(arena);

    // Test 3: ACTIVATION_SIGMOID - gradient scaled by sigmoid derivative
    double input3[] = {0.0};
    double weights3[] = {0.0};
    // z = 0, sigmoid(0) = 0.5, cache = output = 0.5
    double *cache3;
    dense_forward(arena, input3, weights3, 1, 1, 1, ACTIVATION_SIGMOID, &cache3);

    double dout3[] = {1.0};
    grad = dense_backward(arena, dout3, input3, weights3, cache3, 1, 1, 1, ACTIVATION_SIGMOID);

    // sigmoid_backward: 1.0 * 0.5 * (1-0.5) = 0.25
    // d_weights = input^T @ d_act = [0] @ [0.25] = [0]
    check(fabs(grad.d_weights[0]) < EPSILON,
          "ACTIVATION_SIGMOID: d_weights with zero input");

    // d_input = d_act @ weights^T = [0.25] @ [0] = [0]
    check(fabs(grad.d_input[0]) < EPSILON,
          "ACTIVATION_SIGMOID: d_input with zero weights");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
