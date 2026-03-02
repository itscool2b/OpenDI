#include <stdio.h>
#include <math.h>
#include "../../../include/pipeline/cross_entropy_backward.h"
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
    printf("=== Testing cross_entropy_backward ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Perfect predictions give zero gradient
    double pred1[] = {0.0, 1.0, 0.0,
                      1.0, 0.0, 0.0};
    double tgt1[] = {0.0, 1.0, 0.0,
                     1.0, 0.0, 0.0};
    double *result = cross_entropy_backward(arena, pred1, tgt1, 2, 3);
    int all_zero = 1;
    for (int i = 0; i < 6; i++){
        if (fabs(result[i]) > EPSILON){
            all_zero = 0;
            break;
        }
    }
    check(all_zero, "Perfect predictions give zero gradient");

    arena_clear(arena);

    // Test 2: Known gradient values
    double pred2[] = {0.7, 0.2, 0.1};
    double tgt2[] = {1.0, 0.0, 0.0};
    result = cross_entropy_backward(arena, pred2, tgt2, 1, 3);
    // grad = (pred - target) / n_samples
    check(fabs(result[0] - (-0.3)) < EPSILON &&
          fabs(result[1] - 0.2) < EPSILON &&
          fabs(result[2] - 0.1) < EPSILON,
          "Known gradient: (pred-target)/n_samples");

    arena_clear(arena);

    // Test 3: Multiple samples
    double pred3[] = {0.9, 0.1,
                      0.3, 0.7};
    double tgt3[] = {1.0, 0.0,
                     0.0, 1.0};
    result = cross_entropy_backward(arena, pred3, tgt3, 2, 2);
    // grad[0] = (0.9-1.0)/2 = -0.05
    // grad[1] = (0.1-0.0)/2 = 0.05
    // grad[2] = (0.3-0.0)/2 = 0.15
    // grad[3] = (0.7-1.0)/2 = -0.15
    check(fabs(result[0] - (-0.05)) < EPSILON &&
          fabs(result[1] - 0.05) < EPSILON &&
          fabs(result[2] - 0.15) < EPSILON &&
          fabs(result[3] - (-0.15)) < EPSILON,
          "Multiple samples gradient");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
