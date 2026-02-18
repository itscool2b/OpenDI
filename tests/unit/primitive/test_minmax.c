#include <stdio.h>
#include <math.h>
#include "primitive/minmax.h"

int main() {
    printf("=== Testing minmax ===\n");
    
    // Test minimum
    float min_result = minmax(0, 3, 5.0f, 2.0f, 8.0f);
    printf("min(5.0, 2.0, 8.0) = %.2f (expected: 2.00)\n", min_result);
    
    // Test maximum
    float max_result = minmax(1, 3, 5.0f, 2.0f, 8.0f);
    printf("max(5.0, 2.0, 8.0) = %.2f (expected: 8.00)\n", max_result);
    
    // Test with negative numbers
    float min_neg = minmax(0, 4, -5.0f, -2.0f, -8.0f, -1.0f);
    printf("min(-5.0, -2.0, -8.0, -1.0) = %.2f (expected: -8.00)\n", min_neg);
    
    // Test single value
    float single = minmax(0, 1, 42.0f);
    printf("min(42.0) = %.2f (expected: 42.00)\n", single);
    
    // Test empty
    float empty = minmax(0, 0);
    printf("min() with 0 args = %f (expected: NAN)\n", empty);
    
    return 0;
}
