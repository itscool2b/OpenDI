#include <stdio.h>
#include <math.h>
#include "../../../include/pipeline/batch_softmax.h"
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
    printf("=== Testing batch_softmax ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Single row sums to 1
    double v1[] = {1.0, 2.0, 3.0};
    double *result = batch_softmax(arena, v1, 1, 3);
    double sum = result[0] + result[1] + result[2];
    check(fabs(sum - 1.0) < EPSILON, "Single row sums to 1");

    arena_clear(arena);

    // Test 2: Ordering preserved
    result = batch_softmax(arena, v1, 1, 3);
    check(result[2] > result[1] && result[1] > result[0],
          "Ordering preserved within row");

    arena_clear(arena);

    // Test 3: Multiple rows each sum to 1
    double v3[] = {1.0, 2.0, 3.0,
                   -1.0, 0.0, 1.0};
    result = batch_softmax(arena, v3, 2, 3);
    double sum1 = result[0] + result[1] + result[2];
    double sum2 = result[3] + result[4] + result[5];
    check(fabs(sum1 - 1.0) < EPSILON && fabs(sum2 - 1.0) < EPSILON,
          "Each row in multi-row batch sums to 1");

    arena_clear(arena);

    // Test 4: Numerical stability with large values
    double v4[] = {1000.0, 1001.0, 1002.0};
    result = batch_softmax(arena, v4, 1, 3);
    int valid = 1;
    for (int i = 0; i < 3; i++){
        if (isnan(result[i]) || isinf(result[i]) || result[i] <= 0.0){
            valid = 0;
            break;
        }
    }
    check(valid, "Numerically stable with large values");

    arena_clear(arena);

    // Test 5: Equal inputs give uniform distribution
    double v5[] = {1.0, 1.0, 1.0, 1.0};
    result = batch_softmax(arena, v5, 1, 4);
    check(fabs(result[0] - 0.25) < EPSILON &&
          fabs(result[1] - 0.25) < EPSILON &&
          fabs(result[2] - 0.25) < EPSILON &&
          fabs(result[3] - 0.25) < EPSILON,
          "Equal inputs give uniform distribution");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
