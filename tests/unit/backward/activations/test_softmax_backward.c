#include <stdio.h>
#include <math.h>
#include "../../../../include/backward/activations/softmax_backward.h"
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
    printf("=== Testing softmax_backward ===\n\n");

    Arena *arena = arena_create(4096);
    if (!arena) {
        printf("Failed to create arena\n");
        return 1;
    }

    // Test 1: Uniform output with uniform dout
    // output = {0.25, 0.25, 0.25, 0.25}, dout = {1, 1, 1, 1}
    // dot = 0.25+0.25+0.25+0.25 = 1.0
    // grad[i] = 0.25 * (1.0 - 1.0) = 0.0
    double dout1[] = {1.0, 1.0, 1.0, 1.0};
    double output1[] = {0.25, 0.25, 0.25, 0.25};
    double *grad = softmax_backward(arena, dout1, output1, 4);
    int all_zero = 1;
    for (int i = 0; i < 4; i++) {
        if (fabs(grad[i]) > EPSILON) all_zero = 0;
    }
    check(all_zero, "Uniform output + uniform dout: all gradients zero");

    arena_clear(arena);

    // Test 2: Known values
    // output = {0.5, 0.3, 0.2}, dout = {1.0, 0.0, 0.0}
    // dot = 1.0*0.5 + 0.0*0.3 + 0.0*0.2 = 0.5
    // grad = {0.5*(1.0-0.5), 0.3*(0.0-0.5), 0.2*(0.0-0.5)}
    //      = {0.25, -0.15, -0.10}
    double dout2[] = {1.0, 0.0, 0.0};
    double output2[] = {0.5, 0.3, 0.2};
    grad = softmax_backward(arena, dout2, output2, 3);
    check(fabs(grad[0] - 0.25) < EPSILON &&
          fabs(grad[1] - (-0.15)) < EPSILON &&
          fabs(grad[2] - (-0.10)) < EPSILON,
          "Known values: correct gradients");

    arena_clear(arena);

    // Test 3: Gradients sum to zero
    double dout3[] = {2.0, -1.0, 3.0};
    double output3[] = {0.6, 0.3, 0.1};
    grad = softmax_backward(arena, dout3, output3, 3);
    double grad_sum = grad[0] + grad[1] + grad[2];
    check(fabs(grad_sum) < EPSILON, "Gradients sum to zero");

    arena_clear(arena);

    // Test 4: Single element
    double dout4[] = {5.0};
    double output4[] = {1.0};
    grad = softmax_backward(arena, dout4, output4, 1);
    // dot = 5.0*1.0 = 5.0, grad = 1.0*(5.0-5.0) = 0.0
    check(fabs(grad[0]) < EPSILON, "Single element: gradient is zero");

    arena_destroy(arena);

    printf("\n=== Results ===\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);

    return test_failed > 0 ? 1 : 0;
}
