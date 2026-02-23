#include <stdio.h>
#include <math.h>
#include "../../../../include/linalg/matricies/matadd.h"
#include "../../../../include/arena.h"

#define EPSILON 1e-10

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
    printf("=== Testing matadd ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Basic 2x2 addition
    double a[] = {1.0, 2.0, 3.0, 4.0};  // 2x2 matrix
    double b[] = {5.0, 6.0, 7.0, 8.0};  // 2x2 matrix
    double *result = matadd(arena, a, b, 2, 2);
    check(fabs(result[0] - 6.0) < EPSILON && 
          fabs(result[1] - 8.0) < EPSILON && 
          fabs(result[2] - 10.0) < EPSILON && 
          fabs(result[3] - 12.0) < EPSILON, 
          "Basic 2x2 matrix addition");

    // Test 2: Addition with zeros
    arena_clear(arena);
    double zeros[] = {0.0, 0.0, 0.0, 0.0};
    result = matadd(arena, a, zeros, 2, 2);
    check(fabs(result[0] - 1.0) < EPSILON && 
          fabs(result[1] - 2.0) < EPSILON && 
          fabs(result[2] - 3.0) < EPSILON && 
          fabs(result[3] - 4.0) < EPSILON, 
          "Addition with zero matrix");

    // Test 3: 3x3 matrix
    arena_clear(arena);
    double c[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    double d[] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    result = matadd(arena, c, d, 3, 3);
    check(fabs(result[4] - 10.0) < EPSILON && 
          fabs(result[8] - 10.0) < EPSILON, 
          "3x3 matrix addition");

    // Test 4: Negative values
    arena_clear(arena);
    double e[] = {1.0, -2.0, 3.0, -4.0};
    double f[] = {-1.0, 2.0, -3.0, 4.0};
    result = matadd(arena, e, f, 2, 2);
    check(fabs(result[0]) < EPSILON && 
          fabs(result[1]) < EPSILON && 
          fabs(result[2]) < EPSILON && 
          fabs(result[3]) < EPSILON, 
          "Addition with negatives (should cancel)");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
