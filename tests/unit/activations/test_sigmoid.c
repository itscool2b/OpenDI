#include <stdio.h>
#include <math.h>
#include "../../../include/activations/sigmoid.h"

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
    printf("=== Testing sigmoid ===\n\n");

    // Test 1: Sigmoid of 0 should be 0.5
    double result = sigmoid(0.0);
    check(fabs(result - 0.5) < EPSILON, "sigmoid(0.0) = 0.5");

    // Test 2: Sigmoid of positive value
    result = sigmoid(2.0);
    check(fabs(result - 0.880797077977882) < 0.0001, "sigmoid(2.0) ~ 0.881");

    // Test 3: Sigmoid of negative value
    result = sigmoid(-2.0);
    check(fabs(result - 0.119202922022117) < 0.0001, "sigmoid(-2.0) ~ 0.119");

    // Test 4: Symmetry property: sigmoid(-x) = 1 - sigmoid(x)
    double pos = sigmoid(1.5);
    double neg = sigmoid(-1.5);
    check(fabs((1.0 - pos) - neg) < EPSILON, "Symmetry: sigmoid(-x) = 1 - sigmoid(x)");

    // Test 5: Large positive value approaches 1
    result = sigmoid(10.0);
    check(result > 0.9999 && result < 1.0, "sigmoid(10.0) approaches 1");

    // Test 6: Large negative value approaches 0
    result = sigmoid(-10.0);
    check(result > 0.0 && result < 0.0001, "sigmoid(-10.0) approaches 0");

    // Test 7: Output is always in range [0, 1]
    // Note: For very large values, sigmoid saturates at 0.0 or 1.0 due to floating point precision
    double test_vals[] = {-100.0, -50.0, -1.0, 0.0, 1.0, 50.0, 100.0};
    int in_range = 1;
    for (int i = 0; i < 7; i++) {
        double r = sigmoid(test_vals[i]);
        if (r < 0.0 || r > 1.0) {
            in_range = 0;
            break;
        }
    }
    check(in_range, "Output always in range [0, 1]");

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
