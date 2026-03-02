#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../../include/pipeline/init_weights.h"
#include "../../../include/random/random_seed.h"

#define EPSILON 1e-1

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
    printf("=== Testing init_weights ===\n\n");

    // Test 1: Returns non-null pointer
    random_seed(42);
    double *w = init_weights(100, 0.0, 0.1);
    check(w != NULL, "Returns non-null pointer");

    // Test 2: Mean is approximately correct
    double sum = 0.0;
    for (int i = 0; i < 100; i++)
        sum += w[i];
    double mean = sum / 100.0;
    check(fabs(mean) < EPSILON, "Mean approximately 0 for mean=0.0");

    // Test 3: Values are within reasonable range for std=0.1
    int in_range = 1;
    for (int i = 0; i < 100; i++){
        if (fabs(w[i]) > 1.0){
            in_range = 0;
            break;
        }
    }
    check(in_range, "Values within reasonable range for std=0.1");

    free(w);

    // Test 4: Different seed gives different weights
    random_seed(42);
    double *w1 = init_weights(10, 0.0, 1.0);
    random_seed(99);
    double *w2 = init_weights(10, 0.0, 1.0);
    int differ = 0;
    for (int i = 0; i < 10; i++){
        if (fabs(w1[i] - w2[i]) > 1e-10){
            differ = 1;
            break;
        }
    }
    check(differ, "Different seeds produce different weights");

    free(w1);
    free(w2);

    // Test 5: Non-zero mean
    random_seed(42);
    double *w3 = init_weights(100, 5.0, 0.1);
    sum = 0.0;
    for (int i = 0; i < 100; i++)
        sum += w3[i];
    mean = sum / 100.0;
    check(fabs(mean - 5.0) < EPSILON, "Mean approximately 5 for mean=5.0");

    free(w3);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
