#include <stdio.h>
#include <math.h>
#include "../../../include/activations/softmax.h"
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
    printf("=== Testing softmax ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Basic softmax computation
    double v1[] = {1.0, 2.0, 3.0};
    double *result = softmax(arena, v1, 3);
    check(result != NULL, "Basic softmax: returns non-null pointer");
    
    // Check that all values are positive
    check(result[0] > 0.0 && result[1] > 0.0 && result[2] > 0.0, 
          "All softmax outputs are positive");
    
    // Check that values sum to 1
    double sum = result[0] + result[1] + result[2];
    check(fabs(sum - 1.0) < EPSILON, "Softmax outputs sum to 1");
    
    // Check ordering is preserved (larger input -> larger output)
    check(result[2] > result[1] && result[1] > result[0], 
          "Ordering preserved: higher input -> higher output");

    arena_clear(arena);

    // Test 2: Equal values give uniform distribution
    double v2[] = {1.0, 1.0, 1.0, 1.0};
    result = softmax(arena, v2, 4);
    double expected = 0.25;
    check(fabs(result[0] - expected) < EPSILON && 
          fabs(result[1] - expected) < EPSILON &&
          fabs(result[2] - expected) < EPSILON &&
          fabs(result[3] - expected) < EPSILON,
          "Equal inputs give uniform distribution");

    arena_clear(arena);

    // Test 3: Single element
    double v3[] = {5.0};
    result = softmax(arena, v3, 1);
    check(fabs(result[0] - 1.0) < EPSILON, "Single element softmax = 1.0");

    arena_clear(arena);

    // Test 4: Large values (numerical stability test)
    double v4[] = {1000.0, 1001.0, 1002.0};
    result = softmax(arena, v4, 3);
    // Should not produce NaN or Inf
    int valid = 1;
    for (int i = 0; i < 3; i++) {
        if (isnan(result[i]) || isinf(result[i]) || result[i] <= 0.0) {
            valid = 0;
            break;
        }
    }
    check(valid, "Numerically stable with large values");
    
    // Sum should still be 1
    sum = result[0] + result[1] + result[2];
    check(fabs(sum - 1.0) < EPSILON, "Large values: outputs sum to 1");

    arena_clear(arena);

    // Test 5: Negative values
    double v5[] = {-1.0, -2.0, -3.0};
    result = softmax(arena, v5, 3);
    check(result[0] > result[1] && result[1] > result[2],
          "Negative values: ordering preserved");
    sum = result[0] + result[1] + result[2];
    check(fabs(sum - 1.0) < EPSILON, "Negative values: outputs sum to 1");

    arena_clear(arena);

    // Test 6: Mixed positive and negative values
    double v6[] = {-5.0, 0.0, 5.0};
    result = softmax(arena, v6, 3);
    check(result[2] > result[1] && result[1] > result[0],
          "Mixed values: correct ordering");
    sum = result[0] + result[1] + result[2];
    check(fabs(sum - 1.0) < EPSILON, "Mixed values: outputs sum to 1");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
