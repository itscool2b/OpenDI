#include <stdio.h>
#include <math.h>
#include "../../../include/loss/cross_entropy.h"

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
    printf("=== Testing cross_entropy ===\n\n");

    // Test 1: Perfect prediction (one-hot target, pred=1.0)
    double pred1[] = {0.0, 1.0, 0.0};
    double targ1[] = {0.0, 1.0, 0.0};
    double result = cross_entropy(pred1, targ1, 3);
    // -1/3 * (0*log(eps) + 1*log(1+eps) + 0*log(eps)) ~ 0.0
    check(fabs(result) < EPSILON, "Perfect prediction gives near-zero loss");

    // Test 2: Worst prediction
    double pred2[] = {1.0, 0.0, 0.0};
    double targ2[] = {0.0, 1.0, 0.0};
    double result2 = cross_entropy(pred2, targ2, 3);
    // Should be high loss since pred[1] is near zero where target is 1
    check(result2 > 10.0, "Wrong prediction gives high loss");

    // Test 3: Uniform prediction
    double pred3[] = {0.5, 0.5};
    double targ3[] = {1.0, 0.0};
    double result3 = cross_entropy(pred3, targ3, 2);
    // -1/2 * (1*log(0.5) + 0*log(0.5)) = -1/2 * (-0.6931) = 0.3466
    check(fabs(result3 - 0.346574) < 1e-4, "Uniform prediction: CE ~ 0.3466");

    // Test 4: Loss is always non-negative
    double pred4[] = {0.7, 0.2, 0.1};
    double targ4[] = {1.0, 0.0, 0.0};
    double result4 = cross_entropy(pred4, targ4, 3);
    check(result4 >= 0.0, "Cross entropy is non-negative");

    // Test 5: Higher confidence in correct class = lower loss
    double pred5a[] = {0.9, 0.1};
    double pred5b[] = {0.6, 0.4};
    double targ5[] = {1.0, 0.0};
    double r5a = cross_entropy(pred5a, targ5, 2);
    double r5b = cross_entropy(pred5b, targ5, 2);
    check(r5a < r5b, "Higher confidence in correct class gives lower loss");

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
