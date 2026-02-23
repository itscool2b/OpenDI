#include <stdio.h>
#include <math.h>
#include "../../../../include/linalg/matricies/mattranspose.h"
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
    printf("=== Testing mattranspose ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Basic 2x2 transpose
    double a[] = {1.0, 2.0, 3.0, 4.0};  // 2x2 matrix
    // Transpose should be: [1, 3, 2, 4] (2x2)
    double *result = mattranspose(arena, a, 2, 2);
    check(fabs(result[0] - 1.0) < EPSILON && 
          fabs(result[1] - 3.0) < EPSILON && 
          fabs(result[2] - 2.0) < EPSILON && 
          fabs(result[3] - 4.0) < EPSILON, 
          "Basic 2x2 matrix transpose");

    // Test 2: 2x3 -> 3x2 transpose
    arena_clear(arena);
    double b[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};  // 2x3 matrix
    // Transpose should be: [1, 4, 2, 5, 3, 6] (3x2)
    result = mattranspose(arena, b, 2, 3);
    check(fabs(result[0] - 1.0) < EPSILON && 
          fabs(result[1] - 4.0) < EPSILON && 
          fabs(result[2] - 2.0) < EPSILON && 
          fabs(result[3] - 5.0) < EPSILON && 
          fabs(result[4] - 3.0) < EPSILON && 
          fabs(result[5] - 6.0) < EPSILON, 
          "2x3 to 3x2 transpose");

    // Test 3: Symmetric matrix (transpose should be same)
    arena_clear(arena);
    double sym[] = {1.0, 2.0, 2.0, 1.0};  // Symmetric 2x2
    result = mattranspose(arena, sym, 2, 2);
    check(fabs(result[0] - 1.0) < EPSILON && 
          fabs(result[1] - 2.0) < EPSILON && 
          fabs(result[2] - 2.0) < EPSILON && 
          fabs(result[3] - 1.0) < EPSILON, 
          "Symmetric matrix transpose");

    // Test 4: Single row (1x3 -> 3x1)
    arena_clear(arena);
    double row[] = {1.0, 2.0, 3.0};  // 1x3
    result = mattranspose(arena, row, 1, 3);
    check(fabs(result[0] - 1.0) < EPSILON && 
          fabs(result[1] - 2.0) < EPSILON && 
          fabs(result[2] - 3.0) < EPSILON, 
          "Single row transpose to column");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
