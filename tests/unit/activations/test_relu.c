#include <stdio.h>
#include <math.h>
#include "../../../include/activations/relu.h"

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
    printf("=== Testing relu ===\n\n");

    // Test 1: Positive value returns itself
    double result = relu(5.0);
    check(fabs(result - 5.0) < EPSILON, "relu(5.0) = 5.0");

    // Test 2: Negative value returns 0
    result = relu(-3.0);
    check(fabs(result - 0.0) < EPSILON, "relu(-3.0) = 0.0");

    // Test 3: Zero returns 0
    result = relu(0.0);
    check(fabs(result - 0.0) < EPSILON, "relu(0.0) = 0.0");

    // Test 4: Large positive value
    result = relu(1000.0);
    check(fabs(result - 1000.0) < EPSILON, "relu(1000.0) = 1000.0");

    // Test 5: Large negative value
    result = relu(-1000.0);
    check(fabs(result - 0.0) < EPSILON, "relu(-1000.0) = 0.0");

    // Test 6: Small positive value
    result = relu(0.001);
    check(fabs(result - 0.001) < EPSILON, "relu(0.001) = 0.001");

    // Test 7: Small negative value
    result = relu(-0.001);
    check(fabs(result - 0.0) < EPSILON, "relu(-0.001) = 0.0");

    // Test 8: Output is never negative
    double test_vals[] = {-100.0, -50.0, -1.0, -0.5, 0.0, 0.5, 1.0, 50.0, 100.0};
    int non_negative = 1;
    for (int i = 0; i < 9; i++) {
        if (relu(test_vals[i]) < 0.0) {
            non_negative = 0;
            break;
        }
    }
    check(non_negative, "Output is never negative");

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
