#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linalg/vectors/vecadd.h"

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
    printf("=== Testing vecadd ===\n\n");

    // Test 1: Basic addition
    double v1[] = {1.0, 2.0, 3.0};
    double v2[] = {4.0, 5.0, 6.0};
    double *result = vecadd(v1, v2, 3);
    check(result != NULL, "Basic addition: returns non-null pointer");
    check(fabs(result[0] - 5.0) < EPSILON && 
          fabs(result[1] - 7.0) < EPSILON && 
          fabs(result[2] - 9.0) < EPSILON, "Basic addition: correct values");
    free(result);

    // Test 2: Addition with zeros
    double v3[] = {0.0, 0.0, 0.0};
    double v4[] = {1.0, 2.0, 3.0};
    result = vecadd(v3, v4, 3);
    check(fabs(result[0] - 1.0) < EPSILON && 
          fabs(result[1] - 2.0) < EPSILON && 
          fabs(result[2] - 3.0) < EPSILON, "Addition with zeros");
    free(result);

    // Test 3: Addition with negative numbers
    double v5[] = {-1.0, -2.0, -3.0};
    double v6[] = {1.0, 2.0, 3.0};
    result = vecadd(v5, v6, 3);
    check(fabs(result[0]) < EPSILON && 
          fabs(result[1]) < EPSILON && 
          fabs(result[2]) < EPSILON, "Addition with negatives (should cancel out)");
    free(result);

    // Test 4: Single element
    double v7[] = {5.0};
    double v8[] = {3.0};
    result = vecadd(v7, v8, 1);
    check(fabs(result[0] - 8.0) < EPSILON, "Single element addition");
    free(result);

    // Test 5: Large values
    double v9[] = {1e10, 1e10, 1e10};
    double v10[] = {1e10, 1e10, 1e10};
    result = vecadd(v9, v10, 3);
    check(fabs(result[0] - 2e10) < EPSILON, "Large values addition");
    free(result);

    // Test 6: Small values (near zero)
    double v11[] = {1e-10, 2e-10, 3e-10};
    double v12[] = {1e-10, 2e-10, 3e-10};
    result = vecadd(v11, v12, 3);
    check(fabs(result[0] - 2e-10) < EPSILON, "Small values addition");
    free(result);

    // Test 7: Mixed positive and negative
    double v13[] = {-5.0, 10.0, -15.0};
    double v14[] = {3.0, -7.0, 20.0};
    result = vecadd(v13, v14, 3);
    check(fabs(result[0] + 2.0) < EPSILON && 
          fabs(result[1] - 3.0) < EPSILON && 
          fabs(result[2] - 5.0) < EPSILON, "Mixed positive/negative addition");
    free(result);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
