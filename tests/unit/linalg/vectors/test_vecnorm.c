#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../../../../include/linalg/vectors/vecnorm.h"

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
    printf("=== Testing vecnorm ===\n\n");

    // Test 1: Basic norm (3-4-5 triangle)
    double v1[] = {3.0, 4.0};
    double result = vecnorm(v1, 2);
    check(fabs(result - 5.0) < EPSILON, "3-4-5 triangle norm");

    // Test 2: Unit vector
    double v2[] = {1.0, 0.0, 0.0};
    result = vecnorm(v2, 3);
    check(fabs(result - 1.0) < EPSILON, "Unit vector norm = 1");

    // Test 3: Zero vector
    double v3[] = {0.0, 0.0, 0.0};
    result = vecnorm(v3, 3);
    check(fabs(result) < EPSILON, "Zero vector norm = 0");

    // Test 4: Single element
    double v4[] = {5.0};
    result = vecnorm(v4, 1);
    check(fabs(result - 5.0) < EPSILON, "Single element norm");

    // Test 5: 3D vector
    double v5[] = {1.0, 2.0, 2.0};
    result = vecnorm(v5, 3);
    // sqrt(1 + 4 + 4) = sqrt(9) = 3
    check(fabs(result - 3.0) < EPSILON, "3D vector norm (1,2,2)");

    // Test 6: Negative values (should be same as positive)
    double v6[] = {-3.0, -4.0};
    result = vecnorm(v6, 2);
    check(fabs(result - 5.0) < EPSILON, "Negative values norm");

    // Test 7: Large values
    double v7[] = {1e10, 1e10, 1e10};
    result = vecnorm(v7, 3);
    // sqrt(3 * 1e20) = sqrt(3) * 1e10
    double expected = sqrt(3.0) * 1e10;
    check(fabs(result - expected) < EPSILON * expected, "Large values norm");

    // Test 8: Small values
    double v8[] = {1e-10, 1e-10, 1e-10};
    result = vecnorm(v8, 3);
    expected = sqrt(3.0) * 1e-10;
    check(fabs(result - expected) < EPSILON * expected, "Small values norm");

    // Test 9: Pythagorean quadruple (2, 3, 6, 7) -> 4 + 9 + 36 = 49 -> 7
    double v9[] = {2.0, 3.0, 6.0};
    result = vecnorm(v9, 3);
    check(fabs(result - 7.0) < EPSILON, "Pythagorean quadruple (2,3,6)");

    // Test 10: High dimensional vector
    double v10[100];
    for (int i = 0; i < 100; i++) {
        v10[i] = 3.0;  // Each element is 3
    }
    result = vecnorm(v10, 100);
    // sqrt(100 * 9) = sqrt(900) = 30
    check(fabs(result - 30.0) < EPSILON, "High dimensional vector (100D, all 3s)");

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
