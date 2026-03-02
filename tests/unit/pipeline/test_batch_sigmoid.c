#include <stdio.h>
#include <math.h>
#include "../../../include/pipeline/batch_sigmoid.h"
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
    printf("=== Testing batch_sigmoid ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Zero input gives 0.5
    double v1[] = {0.0};
    double *result = batch_sigmoid(arena, v1, 1);
    check(fabs(result[0] - 0.5) < EPSILON, "sigmoid(0) = 0.5");

    arena_clear(arena);

    // Test 2: Large positive value approaches 1
    double v2[] = {10.0};
    result = batch_sigmoid(arena, v2, 1);
    check(result[0] > 0.999, "sigmoid(10) approaches 1");

    arena_clear(arena);

    // Test 3: Large negative value approaches 0
    double v3[] = {-10.0};
    result = batch_sigmoid(arena, v3, 1);
    check(result[0] < 0.001, "sigmoid(-10) approaches 0");

    arena_clear(arena);

    // Test 4: All outputs in (0, 1)
    double v4[] = {-5.0, -1.0, 0.0, 1.0, 5.0};
    result = batch_sigmoid(arena, v4, 5);
    int valid = 1;
    for (int i = 0; i < 5; i++){
        if (result[i] <= 0.0 || result[i] >= 1.0){
            valid = 0;
            break;
        }
    }
    check(valid, "All outputs in range (0, 1)");

    arena_clear(arena);

    // Test 5: Ordering preserved
    double v5[] = {-2.0, 0.0, 2.0};
    result = batch_sigmoid(arena, v5, 3);
    check(result[2] > result[1] && result[1] > result[0],
          "Ordering preserved: higher input -> higher output");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
