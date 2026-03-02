#include <stdio.h>
#include <math.h>
#include "../../../include/pipeline/dense_forward.h"
#include "../../../include/arena.h"

#define EPSILON 1e-6

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
    printf("=== Testing dense_forward ===\n\n");

    Arena *arena = arena_create(65536);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: ACTIVATION_NONE - just matmul
    // [1 2] @ [1] = [1*1 + 2*2] = [5]
    // [3 4]   [2]   [3*1 + 4*2]   [11]
    double input1[] = {1.0, 2.0, 3.0, 4.0};
    double weights1[] = {1.0, 2.0};
    double *cache = NULL;
    double *result = dense_forward(arena, input1, weights1, 2, 2, 1, ACTIVATION_NONE, &cache);
    check(fabs(result[0] - 5.0) < EPSILON && fabs(result[1] - 11.0) < EPSILON,
          "ACTIVATION_NONE: correct matmul result");
    check(cache == NULL, "ACTIVATION_NONE: cache is NULL");

    arena_clear(arena);

    // Test 2: ACTIVATION_RELU - matmul + relu
    double input2[] = {1.0, -1.0, -2.0, 1.0};
    double weights2[] = {1.0, 1.0};
    // matmul: [1*1 + (-1)*1] = [0], [(-2)*1 + 1*1] = [-1]
    // relu: [0, 0]
    result = dense_forward(arena, input2, weights2, 2, 2, 1, ACTIVATION_RELU, &cache);
    check(fabs(result[0]) < EPSILON && fabs(result[1]) < EPSILON,
          "ACTIVATION_RELU: relu applied after matmul");
    check(cache != NULL, "ACTIVATION_RELU: cache stores pre-activation z");

    arena_clear(arena);

    // Test 3: ACTIVATION_SIGMOID - matmul + sigmoid
    double input3[] = {0.0};
    double weights3[] = {1.0};
    result = dense_forward(arena, input3, weights3, 1, 1, 1, ACTIVATION_SIGMOID, &cache);
    check(fabs(result[0] - 0.5) < EPSILON,
          "ACTIVATION_SIGMOID: sigmoid(0) = 0.5");
    check(cache != NULL, "ACTIVATION_SIGMOID: cache stores post-activation output");
    check(fabs(cache[0] - 0.5) < EPSILON, "ACTIVATION_SIGMOID: cache = output");

    arena_clear(arena);

    // Test 4: ACTIVATION_SOFTMAX - matmul + per-row softmax
    double input4[] = {1.0, 0.0, 0.0, 1.0};
    double weights4[] = {1.0, 2.0, 3.0, 3.0, 2.0, 1.0};
    // matmul: [1 0] @ [[1 2 3],[3 2 1]] = [1 2 3]
    //         [0 1]                        [3 2 1]
    result = dense_forward(arena, input4, weights4, 2, 2, 3, ACTIVATION_SOFTMAX, &cache);
    double sum1 = result[0] + result[1] + result[2];
    double sum2 = result[3] + result[4] + result[5];
    check(fabs(sum1 - 1.0) < EPSILON && fabs(sum2 - 1.0) < EPSILON,
          "ACTIVATION_SOFTMAX: each row sums to 1");
    check(result[2] > result[1] && result[1] > result[0],
          "ACTIVATION_SOFTMAX: row 1 ordering preserved");
    check(result[3] > result[4] && result[4] > result[5],
          "ACTIVATION_SOFTMAX: row 2 ordering preserved");

    arena_clear(arena);

    // Test 5: NULL cache is accepted
    result = dense_forward(arena, input3, weights3, 1, 1, 1, ACTIVATION_RELU, NULL);
    check(result != NULL, "NULL cache pointer accepted");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
