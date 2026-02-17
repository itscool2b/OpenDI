#include <stdio.h>
#include "primitive/rounding.h"

int main() {
    printf("=== Testing roundval ===\n");
    
    // Test floor with positive numbers
    double floor_pos = roundval("floor", 3.7);
    printf("floor(3.7) = %.2f (expected: 3.00)\n", floor_pos);
    
    // Test floor with negative numbers
    double floor_neg = roundval("floor", -3.7);
    printf("floor(-3.7) = %.2f (expected: -4.00)\n", floor_neg);
    
    // Test ceil with positive numbers
    double ceil_pos = roundval("ceil", 3.2);
    printf("ceil(3.2) = %.2f (expected: 4.00)\n", ceil_pos);
    
    // Test ceil with negative numbers
    double ceil_neg = roundval("ceil", -3.2);
    printf("ceil(-3.2) = %.2f (expected: -3.00)\n", ceil_neg);
    
    // Test exact values
    double floor_exact = roundval("floor", 5.0);
    printf("floor(5.0) = %.2f (expected: 5.00)\n", floor_exact);
    
    double ceil_exact = roundval("ceil", 5.0);
    printf("ceil(5.0) = %.2f (expected: 5.00)\n", ceil_exact);
    
    // Test invalid decision
    double invalid = roundval("round", 3.5);
    printf("round(3.5) with invalid = %.2f\n", invalid);
    
    return 0;
}
